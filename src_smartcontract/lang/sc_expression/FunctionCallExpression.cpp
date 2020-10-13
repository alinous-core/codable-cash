/*
 * FunctionCallExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression/FunctionCallExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedClass.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/TypeResolver.h"

#include "lang/sc_declare/ClassDeclare.h"
#include "lang/sc_declare/MethodDeclare.h"

#include "lang/sc_expression/VariableIdentifier.h"

#include "engine/sc_analyze_functions/VTableRegistory.h"
#include "engine/sc_analyze_functions/VTableClassEntry.h"
#include "engine/sc_analyze_functions/VTableMethodEntry.h"

#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

#include "vm/variable_access/StackVariableAccess.h"
#include "vm/variable_access/FunctionArguments.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "engine/sc/SmartContract.h"

#include "vm/VirtualMachine.h"

#include "instance/VmClassInstance.h"

#include "instance/instance_ref/AbstractReference.h"
#include "instance/instance_ref/ObjectReference.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_exception/ExceptionInterrupt.h"


namespace alinous {

FunctionCallExpression::FunctionCallExpression() : AbstractExpression(CodeElement::EXP_FUNCTIONCALL) {
	this->name = nullptr;
	this->strName = nullptr;
	this->methodEntry = nullptr;
	this->thisAccess = nullptr;
	this->callSignature = nullptr;
	this->noVirtual = false;
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

	setThrowsException(true);
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
	if(isSuperConstructorCall()){
		analyzeSuperConstructorEntry(actx);
		return;
	}

	bool staticMode = isStaticMode();

	analyzeArguments(actx);

	AnalyzedClass* athisClass = actx->getThisClass();
	analyzeMethodEntry(actx, athisClass, staticMode);

	if(this->methodEntry == nullptr){
		return;
	}

	// this ptr
	if(!staticMode && !this->methodEntry->isStatic()){
		AnalyzeStackManager* astack = actx->getAnalyzeStackManager();
		this->thisAccess = astack->getThisPointer();
		this->thisAccess->analyze(actx, nullptr, this);
	}
}

void FunctionCallExpression::analyzeSuperConstructorEntry(AnalyzeContext* actx) {
	bool staticMode = isStaticMode();
	if(staticMode){
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_CALL_NOSTATIC, this, L"The static method can't use super class constructor.", {});
		return;
	}

	if(!isOnConstructor()){
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_USE_SUPER_CONSTRUCTOR, this, L"The non-constructor method can't use super class constructor.", {});
		return;
	}

	analyzeArguments(actx);

	AnalyzedClass* athisClass = actx->getThisClass();

	AnalyzedClass* superClass = athisClass->getExtends();
	if(superClass == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_USE_SUPER_CONSTRUCTOR, this, L"the class don't have super class.", {});
		return;
	}

	const UnicodeString* name = superClass->getClassDeclare()->getName();
	const UnicodeString* fqn = superClass->getFullQualifiedName();

	ArrayList<AnalyzedType> typeList;
	typeList.setDeleteOnExit();

	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		AnalyzedType type = exp->getType(actx);
		typeList.addElement(new AnalyzedType(type));
	}

	VTableRegistory* vreg = actx->getVtableRegistory();
	VTableClassEntry* classEntry = vreg->getClassEntry(fqn, superClass);

	actx->setCurrentElement(this);
	this->methodEntry = classEntry->findEntry(actx, name, &typeList);
	if(this->methodEntry == nullptr){
		// has no functions to call
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_NAME, actx->getCurrentElement(), L"The method '{0}()' does not exists.", {this->strName});
		return;
	}

	this->callSignature = this->methodEntry->getMethod()->getCallSignature();

	// this ptr
	if(!staticMode && !this->methodEntry->isStatic()){
		AnalyzeStackManager* astack = actx->getAnalyzeStackManager();
		this->thisAccess = astack->getThisPointer();
		this->thisAccess->analyze(actx, nullptr, this);
	}
}

bool FunctionCallExpression::isOnConstructor() const noexcept {
	const CodeElement* element = this;

	while(element != nullptr){
		short kind = element->getKind();
		if(kind == CodeElement::METHOD_DECLARE){
			const MethodDeclare* method = dynamic_cast<const MethodDeclare*>(element);
			return method->isConstructor();
		}

		element = element->getParent();
	}

	return false;
}

void FunctionCallExpression::analyze(AnalyzeContext* actx, AnalyzedClass* athisClass, AbstractVariableInstraction* lastInst) {
	bool staticMode = false;

	analyzeArguments(actx);
	analyzeMethodEntry(actx, athisClass, staticMode);

	MethodDeclare* methodDeclare = this->methodEntry->getMethod();
	staticMode = isStaticMode();

	uint8_t instType = lastInst->getType();
	if(instType == AbstractVariableInstraction::INSTRUCTION_CLASS_TYPE && !methodDeclare->isStatic()){
		if(staticMode){
			// error
			actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_CALL_NOSTATIC, actx->getCurrentElement(), L"The method can't invoke non-static method '{0}()'.", {this->strName});
			return;
		}

		TypeResolver* resolver = actx->getTypeResolver();

		AnalyzedType* thisType = resolver->getClassType(this); __STP(thisType);
		AnalyzedClass* thisClass = thisType->getAnalyzedClass();

		AnalyzedType at = lastInst->getAnalyzedType();
		AnalyzedClass* sprcifiedClass = at.getAnalyzedClass();
		if(!thisClass->hasBaseClass(sprcifiedClass)){
			actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_INCOMPATIBLE_THIS, actx->getCurrentElement(), L"The method can't invoke non-static method '{0}()'.", {this->strName});
			return;
		}
	}

	if(instType == AbstractVariableInstraction::INSTRUCTION_CLASS_TYPE){
		this->noVirtual = true;
	}
}

void FunctionCallExpression::analyzeArguments(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->analyze(actx);
	}
}

void FunctionCallExpression::analyzeMethodEntry(AnalyzeContext* actx, AnalyzedClass* athisClass, bool staticMode) {
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
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_NAME, actx->getCurrentElement(), L"The method '{0}()' does not exists or argument type is wrong.", {this->strName});
		return;
	}

	// check static
	if(staticMode && !this->methodEntry->isStatic()){
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_CALL_NOSTATIC, actx->getCurrentElement(), L"The method can't invoke non-static method.'{0}()' ", {this->strName});
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
	if(this->methodEntry == nullptr){
		return AnalyzedType(AnalyzedType::TYPE_NONE);
	}

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

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);
	interpretArguments(vm, &args, &releaser);

	if(!this->noVirtual && this->methodEntry->isVirtual()){
		return interpretVirtual(vm, &args);
	}

	MethodDeclare* methodDeclare = this->methodEntry->getMethod();
	methodDeclare->interpret(&args, vm);

	ExceptionInterrupt::interruptPoint(vm);

	return args.getReturnedValue();
}

AbstractVmInstance* FunctionCallExpression::interpret(VirtualMachine* vm, VmClassInstance* classInst) {
	MethodDeclare* methodDeclare = this->methodEntry->getMethod();
	if(methodDeclare->isStatic()){
		return interpretStatic(vm, classInst, methodDeclare);
	}

	FunctionArguments args;
	args.setThisPtr(classInst);

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);
	interpretArguments(vm, &args, &releaser);

	if(!this->noVirtual && this->methodEntry->isVirtual()){
		return interpretVirtual(vm, &args);
	}

	methodDeclare->interpret(&args, vm);

	ExceptionInterrupt::interruptPoint(vm);

	return args.getReturnedValue();
}

AbstractVmInstance* FunctionCallExpression::interpretStatic(VirtualMachine* vm,	VmClassInstance* classInst, MethodDeclare* methodDeclare) {
	FunctionArguments args;

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);
	interpretArguments(vm, &args, &releaser);

	methodDeclare->interpret(&args, vm);

	ExceptionInterrupt::interruptPoint(vm);

	return args.getReturnedValue();
}

void FunctionCallExpression::interpretThisPointer(VirtualMachine* vm, FunctionArguments* args) {
	MethodDeclare* methodDeclare = this->methodEntry->getMethod();

	if(!methodDeclare->isStatic()){
		AbstractVmInstance* inst = this->thisAccess->interpret(vm, nullptr);
		ObjectReference* classRef = dynamic_cast<ObjectReference*>(inst);
		assert(classRef != nullptr);

		VmClassInstance* classInst = dynamic_cast<VmClassInstance*>(classRef->getInstance());

		args->setThisPtr(classInst);
	}
}

void FunctionCallExpression::interpretArguments(VirtualMachine* vm,	FunctionArguments* args, StackFloatingVariableHandler* releaser) {
	MethodDeclare* methodDeclare = this->methodEntry->getMethod();

	// arguments
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);

		AbstractVmInstance* inst = exp->interpret(vm);
		releaser->registerInstance(inst);

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

	ExceptionInterrupt::interruptPoint(vm);

	return args->getReturnedValue();
}

bool FunctionCallExpression::isSuperConstructorCall() const noexcept {
	VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(this->name);

	return valId != nullptr ? valId->isSuper() : false;
}

} /* namespace alinous */
