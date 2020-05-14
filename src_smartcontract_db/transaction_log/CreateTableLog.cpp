/*
 * CreateTableLog.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "transaction_log/CreateTableLog.h"

#include "base_io/ByteBuffer.h"

#include "table/CdbTable.h"

#include "transaction/SchemaObjectIdPublisher.h"
#include "transaction/CdbTransactionManager.h"


namespace codablecash {

CreateTableLog::CreateTableLog() : AbstractDdlLog(AbstractTransactionLog::TRX_CREATE_TABLE) {
	this->table = nullptr;
}

CreateTableLog::~CreateTableLog() {
	delete this->table;
}

int CreateTableLog::binarySize() const {
	checkNotNull(this->table);
	int total = sizeof(uint8_t);

	total += this->table->binarySize();

	return total;
}

void CreateTableLog::toBinary(ByteBuffer* out) const {
	checkNotNull(this->table);

	out->put(AbstractTransactionLog::TRX_CREATE_TABLE);
	this->table->toBinary(out);
}

void CreateTableLog::fromBinary(ByteBuffer* in) {

}

void CreateTableLog::commit(CdbTransactionManager* trxManager) {
	SchemaObjectIdPublisher* publisher= trxManager->getSchemaObjectIdPublisher();
	this->table->assignNewOid(publisher);

	// FIXME create table
}


void CreateTableLog::setTable(CdbTable* table) noexcept {
	this->table = table;
}

} /* namespace codablecash */
