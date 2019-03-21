/*
 * TableList.cpp
 *
 *  Created on: 2019/02/27
 *      Author: iizuka
 */

#include "sql_join_parts/TableList.h"
#include "sql_join_parts/TableIdentifier.h"

namespace alinous {

TableList::TableList() : AbstractJoinPart(CodeElement::SQL_EXP_TABLE_LIST) {
}

TableList::~TableList() {
	this->list.deleteElements();
}

void TableList::addTable(AbstractJoinPart* tableId) noexcept {
	this->list.addElement(tableId);
}

int TableList::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();

	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinPart* tableId = this->list.get(i);
		total += tableId->binarySize();
	}

	return total;
}

void TableList::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_TABLE_LIST);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractJoinPart* tableId = this->list.get(i);
		tableId->toBinary(out);
	}
}

void TableList::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkIsJoinPart(element);
		AbstractJoinPart* tableId = dynamic_cast<AbstractJoinPart*>(element);

		this->list.addElement(tableId);
	}
}

} /* namespace alinous */
