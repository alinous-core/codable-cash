/*
 * AbstractArithmeticBinaryExpresson.cpp
 *
 *  Created on: 2020/03/05
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/AbstractArithmeticBinaryExpresson.h"

#include "sc_analyze/AnalyzeContext.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

AbstractArithmeticBinaryExpresson::AbstractArithmeticBinaryExpresson(int kind) : AbstractBinaryExpression(kind), operations(8) {

}

AbstractArithmeticBinaryExpresson::~AbstractArithmeticBinaryExpresson() {

}

AnalyzedType AbstractArithmeticBinaryExpresson::getType(AnalyzeContext* actx) {
	return this->atype;
}

int AbstractArithmeticBinaryExpresson::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}

	return total;
}

void AbstractArithmeticBinaryExpresson::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_ADD);
	AbstractBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void AbstractArithmeticBinaryExpresson::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

} /* namespace alinous */
