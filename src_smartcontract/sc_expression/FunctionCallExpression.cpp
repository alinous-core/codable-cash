/*
 * FunctionCallExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/FunctionCallExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/ValidationError.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/MethodDeclare.h"

#include "sc_expression/VariableIdentifier.h"

#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/VTableClassEntry.h"
#include "sc_analyze_functions/VTableMethodEntry.h"

#include "sc_analyze_stack/AnalyzeStackManager.h"

#include "variable_access/StackVariableAccess.h"
#include "variable_access/FunctionArguments.h"

#include "base/UnicodeString.h"

#include "sc/SmartContract.h"

#include "vm/VirtualMachine.h"

#include "instance/VmClassInstance.h"

#include "instance_ref/AbstractReference.h"
#include "instance_ref/ObjectReference.h"

namespace alinous {

FunctionCallExpression::FunctionCallExpression() : AbstractExpression(CodeElement::EXP_FUNCTIONCALL) {
	this->name = nullptr;
	this->strName = nullptr;
	this->methodEntry = nullptr;
	this->thisAccess = nullptr;
	this->callSignature = nullptr;
}

FunctionCallExpression::~FunctionCallExpression() {
	delete this->name;
	this->args.deleteElements();
	delete this->strName;
	delete this->thisAccess;
	this->callSignature = nullptr;
}

void FunctionCallExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->setParent(this);
		exp->preAnalyze(actx);
	}

	VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(this->name);
	if(valId == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_NAME, this, L"Function identifier must be string starts with alphabet.", {});
		return;
	}

	const UnicodeString* str = valId->getName();
	this->strName = new UnicodeString(str);
}

void FunctionCallExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->analyzeTypeRef(actx);
	}
}

/**
 * needs actx->setThisClass
 */
void FunctionCallExpression::analyze(AnalyzeContext* actx) {
	analyzeArguments(actx);

	AnalyzedClass* athisClass = actx->getThisClass();
	analyzeMethodEntry(actx, athisClass);

	// this ptr
	if(!this->methodEntry->isStatic()){
		AnalyzeStackManager* astack = actx->getAnalyzeStackManager();
		this->thisAccess = astack->getThisPointer();
		this->thisAccess->analyze(actx, nullptr, this);
	}
}

void FunctionCallExpression::analyze(AnalyzeContext* actx, AnalyzedClass* athisClass) {
	analyzeArguments(actx);
	analyzeMethodEntry(actx, athisClass);
}

void FunctionCallExpression::analyzeArguments(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->analyze(actx);
	}
}

void FunctionCallExpression::analyzeMethodEntry(AnalyzeContext* actx, AnalyzedClass* athisClass) {
	ClassDeclare* classDec = athisClass->getClassDeclare();
	const UnicodeString* fqn = classDec->getFullQualifiedName();

	VTableRegistory* vreg = actx->getVtableRegistory();
	VTableClassEntry* classEntry = vreg->getClassEntry(fqn, athisClass);

	ArrayList<AnalyzedType> typeList;
	typeList.setDeleteOnExit();

	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		AnalyzedType type = exp->getType(actx);
		typeList.addElement(new AnalyzedType(type));
	}

	actx->setCurrentElement(this);
	this->methodEntry = classEntry->findEntry(actx, this->strName, &typeList);
	if(this->methodEntry == nullptr){
		// has no functions to call
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_NAME, actx->getCurrentElement(), L"The method '{0}()' does not exists.", {this->strName});
		return;
	}

	this->callSignature = this->methodEntry->getMethod()->getCallSignature();
}

void FunctionCallExpression::setName(AbstractExpression* exp) noexcept {
	this->name = exp;
}

VariableIdentifier* FunctionCallExpression::getName() const noexcept {
	VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(this->name);
	return valId;
}

void FunctionCallExpression::addArgument(AbstractExpression* exp) noexcept {
	this->args.addElement(exp);
}

int FunctionCallExpression::binarySize() const {
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

void FunctionCallExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::EXP_FUNCTIONCALL);
	this->name->toBinary(out);

	int maxLoop = this->args.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->toBinary(out);
	}
}

void FunctionCallExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_VARIABLE_ID);

	this->name = dynamic_cast<VariableIdentifier*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkIsExp(element);
		AbstractExpression* exp = dynamic_cast<AbstractExpression*>(element);

		this->args.addElement(exp);
	}
}

AnalyzedType FunctionCallExpression::getType(AnalyzeContext* actx) {
	MethodDeclare* method = this->methodEntry->getMethod();

	// analyze function type
	return *method->getReturnedType();
}

void FunctionCallExpression::init(VirtualMachine* vm) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->init(vm);
	}
}

AbstractVmInstance* FunctionCallExpression::interpret(VirtualMachine* vm) {
	FunctionArguments args;
	interpretThisPointer(vm, &args);
	interpretArguments(vm, &args);

	if(this->methodEntry->isVirtual()){
		return interpretVirtual(vm, &args);
	}

	MethodDeclare* methodDeclare = this->methodEntry->getMethod();
	methodDeclare->interpret(&args, vm);

	return args.getReturnedValue();
}

AbstractVmInstance* FunctionCallExpression::interpret(VirtualMachine* vm, VmClassInstance* classInst) {
	FunctionArguments args;
	args.setThisPtr(classInst);
	interpretArguments(vm, &args);

	if(this->methodEntry->isVirtual()){
		return interpretVirtual(vm, &args);
	}

	MethodDeclare* methodDeclare = this->methodEntry->getMethod();
	methodDeclare->interpret(&args, vm);

	return args.getReturnedValue();
}

void FunctionCallExpression::interpretThisPointer(VirtualMachine* vm, FunctionArguments* args) {
	MethodDeclare* methodDeclare = this->methodEntry->getMethod();

	// this ptr
	if(!methodDeclare->isStatic()){
		AbstractVmInstance* inst = this->thisAccess->interpret(vm, nullptr);
		ObjectReference* classRef = dynamic_cast<ObjectReference*>(inst);
		assert(classRef != nullptr);

		VmClassInstance* classInst = dynamic_cast<VmClassInstance*>(classRef->getInstance());

		args->setThisPtr(classInst);
	}
}

void FunctionCallExpression::interpretArguments(VirtualMachine* vm,	FunctionArguments* args) {
	MethodDeclare* methodDeclare = this->methodEntry->getMethod();

	// arguments
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		AbstractVmInstance* inst = exp->interpret(vm);

		if(inst->isReference()){
			AbstractReference* ref = dynamic_cast<AbstractReference*>(inst);
			assert(ref != nullptr);
			args->addReference(ref);
		}
		else{
			VmClassInstance* clazzInst = dynamic_cast<VmClassInstance*>(inst);
			assert(clazzInst != nullptr);

			ObjectReference* ref = ObjectReference::createObjectReference(clazzInst, vm, true);
			args->addReference(ref);
		}
	}
}

AbstractVmInstance* FunctionCallExpression::interpretVirtual(VirtualMachine* vm, FunctionArguments* args) {
	SmartContract* sc = vm->getSmartContract();
	AnalyzeContext* actx = sc->getAnalyzeContext();
	VTableRegistory* vreg = actx->getVtableRegistory();

	VmClassInstance* classInst = args->getThisPtr();
	assert(classInst != nullptr);

	AnalyzedClass* aclass = classInst->getAnalyzedClass();
	const UnicodeString* fqn = aclass->getFullQualifiedName();
	VTableClassEntry* classEntry = vreg->getClassEntry(fqn, aclass);

	VTableMethodEntry* entry = classEntry->getVTableMethodEntry(this->callSignature);
	MethodDeclare* methodDeclare = entry->getMethod();

	methodDeclare->interpret(args, vm);

	return args->getReturnedValue();
}

} /* namespace alinous */
