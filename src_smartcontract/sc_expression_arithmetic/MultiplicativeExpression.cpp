/*
 * MultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/MultiplicativeExpression.h"


namespace alinous {

MultiplicativeExpression::MultiplicativeExpression() : AbstractBinaryExpression(CodeElement::EXP_MUL), operations(8) {
}

MultiplicativeExpression::~MultiplicativeExpression() {
}

void MultiplicativeExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void MultiplicativeExpression::analyzeType(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void MultiplicativeExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	// FIXME analyze type
}

void MultiplicativeExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int MultiplicativeExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}

	return total;
}

void MultiplicativeExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_MUL);
	AbstractBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void MultiplicativeExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

AnalyzedType MultiplicativeExpression::getType() {
	return this->atype;
}

AbstractVmInstance* MultiplicativeExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
