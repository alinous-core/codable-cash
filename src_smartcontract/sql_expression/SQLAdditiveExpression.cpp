/*
 * SQLAdditiveExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLAdditiveExpression.h"

namespace alinous {

SQLAdditiveExpression::SQLAdditiveExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_ADDITIVE), operations(4) {
}

SQLAdditiveExpression::~SQLAdditiveExpression() {
}

void SQLAdditiveExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int SQLAdditiveExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}
	return total;
}

void SQLAdditiveExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_ADDITIVE);
	AbstractSQLBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void SQLAdditiveExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

AbstractVmInstance* SQLAdditiveExpression::interpret(VirtualMachine* vm) {
	// FIXME SQLAdditiveExpression
	return nullptr;
}


} /* namespace alinous */
