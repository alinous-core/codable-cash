/*
 * SQLFunctionCall.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "sql_expression/SQLFunctionCall.h"
#include "sc_expression/VariableIdentifier.h"

namespace alinous {

SQLFunctionCall::SQLFunctionCall() : AbstractSQLExpression(CodeElement::SQL_EXP_FUNCTION_CALL) {
	this->name = nullptr;
}

SQLFunctionCall::~SQLFunctionCall() {
	delete this->name;
	this->arguments.deleteElements();
}

void SQLFunctionCall::setName(VariableIdentifier* name) noexcept {
	this->name = name;
}

void SQLFunctionCall::addArgument(AbstractSQLExpression* arg) noexcept {
	this->arguments.addElement(arg);
}

} /* namespace alinous */

int alinous::SQLFunctionCall::binarySize() const {
}

void alinous::SQLFunctionCall::toBinary(ByteBuffer* out) {
}

void alinous::SQLFunctionCall::fromBinary(ByteBuffer* in) {
}
