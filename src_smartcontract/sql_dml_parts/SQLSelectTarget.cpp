/*
 * SQLSelectTarget.cpp
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLSelectTarget.h"
#include "base/UnicodeString.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLSelectTarget::SQLSelectTarget() {
	this->wildcard = false;
	this->exp = nullptr;
	this->asName = nullptr;
}

SQLSelectTarget::~SQLSelectTarget() {
	delete this->exp;
	delete this->asName;
}

void SQLSelectTarget::setWildcard(bool wildcard) noexcept {
	this->wildcard = wildcard;
}

void SQLSelectTarget::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

void SQLSelectTarget::setAsName(UnicodeString* asName) noexcept {
	this->asName = asName;
}

int SQLSelectTarget::binarySize() const {
}

void SQLSelectTarget::toBinary(ByteBuffer* out) {
}

void SQLSelectTarget::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
