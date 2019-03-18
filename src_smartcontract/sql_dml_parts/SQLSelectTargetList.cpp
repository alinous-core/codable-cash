/*
 * SQLSelectTargetList.cpp
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLSelectTargetList.h"
#include "sql_dml_parts/SQLSelectTarget.h"

namespace alinous {

SQLSelectTargetList::SQLSelectTargetList() {
}

SQLSelectTargetList::~SQLSelectTargetList() {
	this->list.deleteElements();
}

void SQLSelectTargetList::addTarget(SQLSelectTarget* target) noexcept {
	this->list.addElement(target);
}

int SQLSelectTargetList::binarySize() const {
}

void SQLSelectTargetList::toBinary(ByteBuffer* out) {
}

void SQLSelectTargetList::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
