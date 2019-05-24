/*
 * AllocationExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/AllocationExpression.h"

#include "sc_declare/PackageNameDeclare.h"
#include "sc_expression/FunctionCallExpression.h"

namespace alinous {

AllocationExpression::AllocationExpression() : AbstractExpression(CodeElement::EXP_ALLOCATION) {
	this->packageName = nullptr;
	this->exp = nullptr;
}

AllocationExpression::~AllocationExpression() {
	delete this->packageName;
	delete this->exp;
}

void AllocationExpression::preAnalyze(AnalyzeContext* actx) {
	// FIXME
}

void AllocationExpression::analyze(AnalyzeContext* actx) {
	// FIXME
}

void AllocationExpression::setPackage(PackageNameDeclare* packageName) noexcept {
	this->packageName = packageName;
}

void AllocationExpression::setExpression(FunctionCallExpression* exp) noexcept {
	this->exp = exp;
}

int AllocationExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);

	if(this->packageName != nullptr){
		total += this->packageName->binarySize();
	}

	total += this->exp->binarySize();

	return total;
}

void AllocationExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_ALLOCATION);

	out->put(this->packageName != nullptr ? 1 : 0);
	if(this->packageName != nullptr){
		this->packageName->toBinary(out);
	}

	this->exp->toBinary(out);
}

void AllocationExpression::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::PACKAGE_NAME_DECLARE);
		this->packageName = dynamic_cast<PackageNameDeclare*>(element);
	}

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_FUNCTIONCALL);
	this->exp = dynamic_cast<FunctionCallExpression*>(element);
}

} /* namespace alinous */
