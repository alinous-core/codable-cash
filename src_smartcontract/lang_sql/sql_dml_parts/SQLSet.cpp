/*
 * SQLSet.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLSet.h"
#include "sql_dml_parts/SQLSetPair.h"

namespace alinous {

SQLSet::SQLSet() : AbstractSQLPart(CodeElement::SQL_PART_SET) {
}

SQLSet::~SQLSet() {
	this->list.deleteElements();
}

void SQLSet::addPair(SQLSetPair* pair) noexcept {
	this->list.addElement(pair);
}

int SQLSet::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		SQLSetPair* pair = this->list.get(i);
		total += pair->binarySize();
	}

	return total;
}

void SQLSet::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_PART_SET);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		SQLSetPair* pair = this->list.get(i);
		pair->toBinary(out);
	}
}

void SQLSet::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_PART_SET_PAIR);
		SQLSetPair* pair = dynamic_cast<SQLSetPair*>(element);

		this->list.addElement(pair);
	}
}

} /* namespace alinous */
