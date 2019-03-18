/*
 * SQLSet.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLSet.h"
#include "sql_dml_parts/SQLSetPair.h"

namespace alinous {

SQLSet::SQLSet() {
}

SQLSet::~SQLSet() {
	this->list.deleteElements();
}

void SQLSet::addPair(SQLSetPair* pair) noexcept {
	this->list.addElement(pair);
}

int SQLSet::binarySize() const {
}

void SQLSet::toBinary(ByteBuffer* out) {
}

void SQLSet::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
