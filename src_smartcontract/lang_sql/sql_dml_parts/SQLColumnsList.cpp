/*
 * SQLColumnsList.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLColumnsList.h"
#include "lang_sql/sql_expression/SQLColumnIdentifier.h"

namespace alinous {

SQLColumnsList::SQLColumnsList() : AbstractSQLPart(CodeElement::SQL_PART_COLUMN_LIST) {
}

SQLColumnsList::~SQLColumnsList() {
	this->list.deleteElements();
}

void SQLColumnsList::addColumn(SQLColumnIdentifier* colId) noexcept {
	this->list.addElement(colId);
}

int SQLColumnsList::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();

	for(int i = 0; i != maxLoop; ++i){
		SQLColumnIdentifier* colId = this->list.get(i);
		total += colId->binarySize();
	}

	return total;
}

int SQLColumnsList::numColumns() const noexcept {
	return this->list.size();
}

void SQLColumnsList::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_PART_COLUMN_LIST);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		SQLColumnIdentifier* colId = this->list.get(i);
		colId->toBinary(out);
	}
}

void SQLColumnsList::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_EXP_COLUMN_ID);

		SQLColumnIdentifier* colId = dynamic_cast<SQLColumnIdentifier*>(element);
		this->list.addElement(colId);
	}
}

} /* namespace alinous */
