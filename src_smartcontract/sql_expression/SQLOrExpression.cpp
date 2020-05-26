/*
 * SQLOrExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLOrExpression.h"

namespace alinous {

SQLOrExpression::SQLOrExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_OR) {
}

SQLOrExpression::~SQLOrExpression() {
}

int SQLOrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	return total;
}

void SQLOrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_OR);
	AbstractSQLBinaryExpression::toBinary(out);
}

void SQLOrExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);
}

AbstractVmInstance* SQLOrExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME SQLOrExpression
}

} /* namespace alinous */
