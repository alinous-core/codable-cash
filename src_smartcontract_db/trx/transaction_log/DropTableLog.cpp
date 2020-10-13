/*
 * DropTableLog.cpp
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#include "trx/transaction_log/DropTableLog.h"
#include "trx/transaction_log/AbstractTransactionLog.h"

#include "trx/transaction/CdbTransactionManager.h"

#include "lang_sql/sql_join_parts/TableIdentifier.h"

#include "base_io/ByteBuffer.h"

#include "schema_table/table/TableObjectFactory.h"

#include "base/StackRelease.h"
namespace codablecash {

DropTableLog::DropTableLog() : AbstractDdlLog(AbstractTransactionLog::TRX_DROP_TABLE) {
	this->tableId = nullptr;
}

DropTableLog::~DropTableLog() {
	delete this->tableId;
}

int DropTableLog::binarySize() const {
	checkNotNull(this->tableId);
	int total = sizeof(uint8_t);

	total += this->tableId->binarySize();

	return total;
}

void DropTableLog::toBinary(ByteBuffer* out) const {
	checkNotNull(this->tableId);

	out->put(AbstractTransactionLog::TRX_DROP_TABLE);
	this->tableId->toBinary(out);
}

void DropTableLog::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	StackRelease<CodeElement> st_element(element);

	TableIdentifier* t = dynamic_cast<TableIdentifier*>(element);

	checkNotNull(t);
	st_element.cancel();

	this->tableId = t;
}

void DropTableLog::commit(CdbTransactionManager* trxManager) {
	trxManager->commitDropTable(this);
}

void DropTableLog::setTableId(const TableIdentifier* tableId) noexcept {
	this->tableId = new TableIdentifier(*tableId);
}

void DropTableLog::inputDefaultSchema(const UnicodeString* schema) {
	this->tableId->inputDefaultSchema(schema);
}


} /* namespace codablecash */
