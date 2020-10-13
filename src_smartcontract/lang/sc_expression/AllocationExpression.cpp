/*
 * AllocationExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression/AllocationExpression.h"

#include "lang/sc_declare/PackageNameDeclare.h"
#include "lang/sc_expression/ConstructorCall.h"
#include "lang/sc_expression/ConstructorArray.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedThisClassStackPopper.h"

#include "instance/VmClassInstance.h"

#include "base/StackRelease.h"

#include "engine/sc_analyze/ValidationError.h"

namespace alinous {

AllocationExpression::AllocationExpression() : AbstractExpression(CodeElement::EXP_ALLOCATION) {
	this->packageName = nullptr;
	this->constructorCall = nullptr;
	this->array = nullptr;
}

AllocationExpression::~AllocationExpression() {
	delete this->packageName;
	delete this->constructorCall;
	delete this->array;
}

void AllocationExpression::preAnalyze(AnalyzeContext* actx) {
	if(this->constructorCall != nullptr){
		this->constructorCall->setParent(this);
		this->constructorCall->preAnalyze(actx);
	}
	if(this->array != nullptr){
		this->array->setParent(this);
		this->array->preAnalyze(actx);
	}
}

void AllocationExpression::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->constructorCall != nullptr){
		this->constructorCall->analyzeTypeRef(actx);
	}
	if(this->array != nullptr){
		this->array->analyzeTypeRef(actx);
	}
}

void AllocationExpression::analyze(AnalyzeContext* actx) {
	if(this->array != nullptr){
		analyzeArray(actx);
		return;
	}

	TypeResolver* typeResolver = actx->getTypeResolver();

	UnicodeString className(L"");
	if(this->packageName != nullptr){
		const UnicodeString* pkgName = this->packageName->getName();
		className.append(pkgName);
		className.append(L".");
	}

	const UnicodeString* constructorName = this->constructorCall->getName();
	className.append(constructorName);

	AnalyzedType* atype = typeResolver->findClassType(this, &className); __STP(atype);
	if(atype == nullptr){
		actx->addValidationError(ValidationError::CODE_ALLOCATION_TYPE_DOES_NOT_EXISTS, this, L"The class '{0}' does not exists.", {&className});
		return;
	}

	if(atype->isInterface()){
		actx->addValidationError(ValidationError::CODE_ALLOCATION_TYPE_IS_INTERFACE, this, L"The class '{0}' is interface.", {&className});
		return;
	}

	AnalyzedThisClassStackPopper popper(actx, atype->getAnalyzedClass());

	this->constructorCall->analyze(actx);
}

void AllocationExpression::analyzeArray(AnalyzeContext* actx) {
	UnicodeString className(L"");
	if(this->packageName != nullptr){
		const UnicodeString* pkgName = this->packageName->getName();
		className.append(pkgName);
		className.append(L".");
	}

	const UnicodeString* constructorName = this->array->getName();
	className.append(constructorName);

	AnalyzedType* atype = findType(actx, &className); __STP(atype);
	if(atype == nullptr){
		actx->addValidationError(ValidationError::CODE_ALLOCATION_TYPE_DOES_NOT_EXISTS, this, L"The class '{0}' does not exists.", {&className});
		return;
	}

	actx->setTmpArrayType(atype);

	this->array->analyze(actx);
}

AnalyzedType* AllocationExpression::findType(AnalyzeContext* actx, const UnicodeString* className) const {
	TypeResolver* typeResolver = actx->getTypeResolver();

	AnalyzedType* atype = typeResolver->findBaseType(className);
	if(atype == nullptr){
		atype = typeResolver->findClassType(this, className);
	}

	return atype;
}

void AllocationExpression::setPackage(PackageNameDeclare* packageName) noexcept {
	this->packageName = packageName;
}

void AllocationExpression::setExpression(ConstructorCall* exp) noexcept {
	this->constructorCall = exp;
}

void AllocationExpression::setConstructorArray(ConstructorArray* array) noexcept {
	this->array = array;
}

int AllocationExpression::binarySize() const {
	//checkNotNull(this->constructorCall);

	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);

	if(this->packageName != nullptr){
		total += this->packageName->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->constructorCall != nullptr){
		total += this->constructorCall->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->array != nullptr){
		total += this->array->binarySize();
	}

	return total;
}

void AllocationExpression::toBinary(ByteBuffer* out) {
	//checkNotNull(this->constructorCall);

	out->putShort(CodeElement::EXP_ALLOCATION);

	out->put(this->packageName != nullptr ? 1 : 0);
	if(this->packageName != nullptr){
		this->packageName->toBinary(out);
	}

	uint8_t bl = (this->constructorCall != nullptr) ? 1 : 0;
	out->put(bl);
	if(this->constructorCall != nullptr){
		this->constructorCall->toBinary(out);
	}

	bl = (this->array != nullptr) ? 1 : 0;
	out->put(bl);
	if(this->array != nullptr){
		this->array->toBinary(out);
	}

}

void AllocationExpression::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::PACKAGE_NAME_DECLARE);
		this->packageName = dynamic_cast<PackageNameDeclare*>(element);
	}

	bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::EXP_CONSTRUCTORCALL);
		this->constructorCall = dynamic_cast<ConstructorCall*>(element);
	}

	bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::EXP_CONSTRUCTORARRAY);
		this->array = dynamic_cast<ConstructorArray*>(element);
	}
}

AnalyzedType AllocationExpression::getType(AnalyzeContext* actx) {
	if(this->array != nullptr){
		return this->array->getType(actx);
	}

	return this->constructorCall->getType(actx);
}

void AllocationExpression::init(VirtualMachine* vm) {
	if(this->array != nullptr){
		this->array->init(vm);
		return;
	}

	this->constructorCall->init(vm);
}

AbstractVmInstance* AllocationExpression::interpret(VirtualMachine* vm) {
	if(this->array != nullptr){
		return interpretArray(vm);
	}

	AbstractVmInstance* inst = this->constructorCall->interpret(vm);

	return inst; // expression::interpret()
}

AbstractVmInstance* AllocationExpression::interpretArray(VirtualMachine* vm) {
	AbstractVmInstance* inst = this->array->interpret(vm);

	return inst;
}

} /* namespace alinous */
