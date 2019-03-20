/*
 * SqlMultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SqlMultiplicativeExpression.h"

namespace alinous {

SqlMultiplicativeExpression::SqlMultiplicativeExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_MULTIPLICATIVE), operations(4) {
}

SqlMultiplicativeExpression::~SqlMultiplicativeExpression() {
}

void SqlMultiplicativeExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int SqlMultiplicativeExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}
	return total;
}

void SqlMultiplicativeExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_MULTIPLICATIVE);
	AbstractSQLBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void SqlMultiplicativeExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

} /* namespace alinous */
