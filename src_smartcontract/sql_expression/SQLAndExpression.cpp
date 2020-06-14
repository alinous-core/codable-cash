/*
 * SQLAndExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLAndExpression.h"

namespace alinous {

SQLAndExpression::SQLAndExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_AND) {
}

SQLAndExpression::~SQLAndExpression() {
}

int SQLAndExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	return total;
}

void SQLAndExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_AND);
	AbstractSQLBinaryExpression::toBinary(out);
}

void SQLAndExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);
}

AbstractVmInstance* SQLAndExpression::interpret(VirtualMachine* vm) {
	// FIXME SQLAndExpression
	return nullptr;
}


} /* namespace alinous */
