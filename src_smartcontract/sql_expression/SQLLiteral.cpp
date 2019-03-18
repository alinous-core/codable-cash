/*
 * SQLLiteral.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLLiteral.h"
#include "base/UnicodeString.h"

namespace alinous {

SQLLiteral::SQLLiteral() : AbstractSQLExpression(CodeElement::SQL_EXP_LITERAL) {
	this->value = nullptr;
	this->type = TYPE_STRING;
}

SQLLiteral::~SQLLiteral() {
	delete this->value;
}

void SQLLiteral::setValue(UnicodeString* value, uint8_t type) noexcept {
	this->value = value;
	this->type = type;
}

} /* namespace alinous */

int alinous::SQLLiteral::binarySize() const {
}

void alinous::SQLLiteral::toBinary(ByteBuffer* out) {
}

void alinous::SQLLiteral::fromBinary(ByteBuffer* in) {
}
