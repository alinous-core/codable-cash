/*
 * ConstructorCall.cpp
 *
 *  Created on: 2020/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression/ConstructorCall.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedClass.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzedThisClassStackPopper.h"

#include "lang/sc_expression/VariableIdentifier.h"

#include "instance/VmClassInstance.h"

#include "base/UnicodeString.h"

#include "lang/sc_declare/ClassDeclare.h"

#include "engine/sc_analyze_functions/VTableClassEntry.h"
#include "engine/sc_analyze_functions/VTableRegistory.h"
#include "engine/sc_analyze_functions/VTableMethodEntry.h"

#include "vm/variable_access/StackVariableAccess.h"
#include "vm/variable_access/FunctionArguments.h"

#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

#include "lang/sc_declare/MethodDeclare.h"

#include "instance/instance_ref/ObjectReference.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_exception/ExceptionInterrupt.h"

#include "engine/sc/SmartContract.h"

#include "instance/instance_ref/VmRootReference.h"
namespace alinous {

ConstructorCall::ConstructorCall() : AbstractExpression(CodeElement::EXP_CONSTRUCTORCALL) {
	this->name = nullptr;
	this->strName = nullptr;
	this->atype = nullptr;
	this->methodEntry = nullptr;
}

ConstructorCall::~ConstructorCall() {
	delete this->name;
	this->args.deleteElements();

	delete this->strName;
	delete this->atype;
}

void ConstructorCall::setName(AbstractExpression* exp) noexcept {
	this->name = exp;
}

const UnicodeString* ConstructorCall::getName() noexcept {
	if(this->strName == nullptr){
		VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(this->name);
		const UnicodeString* n = valId->getName();
		this->strName = new UnicodeString(n);
	}

	return this->strName;
}

void ConstructorCall::addArgument(AbstractExpression* exp) noexcept {
	this->args.addElement(exp);
}


void ConstructorCall::init(VirtualMachine* vm) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->init(vm);
	}
}

int ConstructorCall::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += this->name->binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		total += exp->binarySize();
	}

	return total;
}

void ConstructorCall::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::EXP_CONSTRUCTORCALL);
	this->name->toBinary(out);

	int maxLoop = this->args.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->toBinary(out);
	}
}

void ConstructorCall::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->name = dynamic_cast<AbstractExpression*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkIsExp(element);
		AbstractExpression* exp = dynamic_cast<AbstractExpression*>(element);

		this->args.addElement(exp);
	}
}

void ConstructorCall::preAnalyze(AnalyzeContext* actx) {
	this->name->setParent(this);
	this->name->preAnalyze(actx);

	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void ConstructorCall::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void ConstructorCall::analyze(AnalyzeContext* actx) {
	{
		// recover this class
		AnalyzedClass* lastThisClass = actx->getLastThisClass();
		AnalyzedThisClassStackPopper popper(actx, lastThisClass);

		int maxLoop = this->args.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractExpression* exp = this->args.get(i);
			exp->analyze(actx);
		}
	}

	AnalyzedClass* aclass = actx->getThisClass();
	this->atype = new AnalyzedType(aclass);

	// Find constructor
	ClassDeclare* classDec = aclass->getClassDeclare();
	const UnicodeString* fqn = classDec->getFullQualifiedName();

	VTableRegistory* vreg = actx->getVtableRegistory();
	VTableClassEntry* classEntry = vreg->getClassEntry(fqn, aclass);


	ArrayList<AnalyzedType> typeList;
	typeList.setDeleteOnExit();

	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		AnalyzedType type = exp->getType(actx);
		typeList.addElement(new AnalyzedType(type));
	}

	actx->setCurrentElement(this);
	const UnicodeString* funcName = getName();
	this->methodEntry = classEntry->findEntry(actx, funcName, &typeList);
	if(this->methodEntry == nullptr){
		// has no functions to call
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_NAME, actx->getCurrentElement(), L"The method '{0}()' does not exists.", {this->strName});
		return;
	}
}

AnalyzedType ConstructorCall::getType(AnalyzeContext* actx) {
	return *this->atype;
}


AbstractVmInstance* ConstructorCall::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AnalyzedClass* clazz = this->atype->getAnalyzedClass();
	VmClassInstance* inst = VmClassInstance::createObject(clazz, vm);

	FunctionArguments args;
	StackFloatingVariableHandler releaser(gc);
	interpretArguments(vm, &args, inst, &releaser);


	MethodDeclare* methodDeclare = this->methodEntry->getMethod();
	methodDeclare->interpret(&args, vm);

	ExceptionInterrupt::interruptPoint(vm, inst);

	return inst;
}

void ConstructorCall::interpretArguments(VirtualMachine* vm, FunctionArguments* args, VmClassInstance* classInst, StackFloatingVariableHandler* releaser) {
	MethodDeclare* methodDeclare = this->methodEntry->getMethod();

	// this ptr
	args->setThisPtr(classInst);

	// arguments
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		AbstractVmInstance* inst = exp->interpret(vm);

		if(inst != nullptr && inst->isReference()){
			AbstractReference* ref = dynamic_cast<AbstractReference*>(inst);
			assert(ref != nullptr);
			args->addSubstance(ref->getInstance());
		}
		else{
			IAbstractVmInstanceSubstance* clazzInst = dynamic_cast<IAbstractVmInstanceSubstance*>(inst);
			//assert(clazzInst != nullptr);

			args->addSubstance(clazzInst);
		}
	}
}

} /* namespace alinous */
