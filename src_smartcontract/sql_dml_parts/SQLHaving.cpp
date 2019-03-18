/*
 * SQLHaving.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLHaving.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLHaving::SQLHaving() {
	this->exp = nullptr;
}

SQLHaving::~SQLHaving() {
	delete this->exp;
}

void alinous::SQLHaving::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */

int alinous::SQLHaving::binarySize() const {
}

void alinous::SQLHaving::toBinary(ByteBuffer* out) {
}

void alinous::SQLHaving::fromBinary(ByteBuffer* in) {
}
