/*
 * AbstractAlterCommandLog.cpp
 *
 *  Created on: 2020/09/16
 *      Author: iizuka
 */

#include "transaction_log_alter/AbstractAlterCommandLog.h"

#include "sql_join_parts/TableIdentifier.h"

namespace codablecash {

AbstractAlterCommandLog::AbstractAlterCommandLog(uint8_t type) : AbstractDdlLog(type) {
	this->tableId = nullptr;
}

AbstractAlterCommandLog::~AbstractAlterCommandLog() {
	delete this->tableId;
}

void AbstractAlterCommandLog::setTableIdentifier(const TableIdentifier* tableId) noexcept {
	this->tableId = new TableIdentifier(*tableId);
}

int AbstractAlterCommandLog::binarySize() const {
	checkNotNull(this->tableId);

	return this->tableId->binarySize();
}

void AbstractAlterCommandLog::toBinary(ByteBuffer* out) const {
	checkNotNull(this->tableId);

	this->tableId->toBinary(out);
}

void AbstractAlterCommandLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);

	CodeElement::checkNotNull(element);
	CodeElement::checkKind(element, CodeElement::SQL_EXP_TABLE_ID);

	this->tableId = dynamic_cast<TableIdentifier*>(element);
}

void AbstractAlterCommandLog::reanalyze(AnalyzeContext* actx, CodeElement* parent) {
}


} /* namespace codablecash */
