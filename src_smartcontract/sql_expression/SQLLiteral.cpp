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

int SQLLiteral::binarySize() const {
	checkNotNull(this->value);

	int total = sizeof(uint16_t);
	total += stringSize(this->value);
	total += sizeof(uint8_t);

	return total;
}

void SQLLiteral::toBinary(ByteBuffer* out) {
	checkNotNull(this->value);

	out->putShort(CodeElement::SQL_EXP_LITERAL);
	putString(out, this->value);
	out->put(this->type);
}

void SQLLiteral::fromBinary(ByteBuffer* in) {
	this->value = getString(in);
	this->type = in->get();
}

} /* namespace alinous */
