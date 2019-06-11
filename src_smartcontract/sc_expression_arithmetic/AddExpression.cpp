/*
 * AddExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/AddExpression.h"


namespace alinous {

AddExpression::AddExpression() : AbstractBinaryExpression(CodeElement::EXP_ADD), operations(8) {
}

AddExpression::~AddExpression() {
}

void AddExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void AddExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	// FIXME analyze type
}

void AddExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int AddExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}

	return total;
}

void AddExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_ADD);
	AbstractBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void AddExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

AnalyzedType AddExpression::getType() {
	return this->atype;
}

} /* namespace alinous */
