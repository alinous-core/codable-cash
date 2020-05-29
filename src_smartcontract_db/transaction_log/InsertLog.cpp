/*
 * InsertLog.cpp
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#include "transaction_log/InsertLog.h"

#include "base_io/ByteBuffer.h"

#include "table_record/CdbRecord.h"
#include "table_record/CdbTableIdentifier.h"

#include "transaction/CdbTransactionManager.h"


namespace codablecash {

InsertLog::InsertLog() : AbstractTransactionLog(AbstractTransactionLog::TRX_INSERT) {
	this->table = nullptr;
}

InsertLog::~InsertLog() {
	delete this->table;
	this->records.deleteElements();
}

int InsertLog::binarySize() const {
	checkNotNull(this->table);

	int total = sizeof(uint8_t);

	total += this->table->binarySize();

	int maxLoop = this->records.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* rec = this->records.get(i);

		total += rec->binarySize();
	}

	return total;
}

void InsertLog::toBinary(ByteBuffer* out) const {
	checkNotNull(this->table);

	out->put(AbstractTransactionLog::TRX_INSERT);

	this->table->toBinary(out);

	int maxLoop = this->records.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* rec = this->records.get(i);

		rec->toBinary(out);
	}
}

void InsertLog::fromBinary(ByteBuffer* in) {
	this->table = CdbTableIdentifier::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* rec = CdbRecord::fromBinary(in);
		addRecord(rec);
	}
}

void InsertLog::commit(CdbTransactionManager* trxManager) {

	trxManager->commitInsert(this);
}

void InsertLog::addRecord(CdbRecord* record) noexcept {
	this->records.addElement(record);
}

void InsertLog::setTable(CdbTableIdentifier* table) noexcept {
	this->table = table;
}

} /* namespace codablecash */
