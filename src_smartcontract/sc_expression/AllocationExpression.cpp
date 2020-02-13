/*
 * AllocationExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/AllocationExpression.h"

#include "sc_declare/PackageNameDeclare.h"
#include "sc_expression/ConstructorCall.h"
#include "sc_expression/ConstructorArray.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedThisClassStackPopper.h"

#include "instance/VmClassInstance.h"

#include "base/StackRelease.h"


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
	this->constructorCall->setParent(this);
	this->constructorCall->preAnalyze(actx);
}

void AllocationExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->constructorCall->analyzeTypeRef(actx);
}

void AllocationExpression::analyze(AnalyzeContext* actx) {
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

	AnalyzedThisClassStackPopper popper(actx, atype->getAnalyzedClass());

	this->constructorCall->analyze(actx);
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
	checkNotNull(this->constructorCall);

	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);

	if(this->packageName != nullptr){
		total += this->packageName->binarySize();
	}

	total += this->constructorCall->binarySize();

	return total;
}

void AllocationExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->constructorCall);

	out->putShort(CodeElement::EXP_ALLOCATION);

	out->put(this->packageName != nullptr ? 1 : 0);
	if(this->packageName != nullptr){
		this->packageName->toBinary(out);
	}

	this->constructorCall->toBinary(out);
}

void AllocationExpression::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::PACKAGE_NAME_DECLARE);
		this->packageName = dynamic_cast<PackageNameDeclare*>(element);
	}

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_CONSTRUCTORCALL);
	this->constructorCall = dynamic_cast<ConstructorCall*>(element);
}

AnalyzedType AllocationExpression::getType(AnalyzeContext* actx) {
	return this->constructorCall->getType(actx);
}

void AllocationExpression::init(VirtualMachine* vm) {
	this->constructorCall->init(vm);
}

AbstractVmInstance* AllocationExpression::interpret(VirtualMachine* vm) {
	AbstractVmInstance* inst = this->constructorCall->interpret(vm);

	return inst; // expression::interpret()
}

} /* namespace alinous */
