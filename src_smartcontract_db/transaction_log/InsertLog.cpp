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
#include "transaction/RecordObjectIdPublisher.h"

#include "base/StackRelease.h"

#include "engine/CdbOid.h"

#include "engine_lock/WriteLockHandle.h"
#include "engine_lock/ReadLockHandle.h"
#include "engine_lock/StackDbLockUnlocker.h"

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
		CdbRecord* rec = CdbRecord::createFromBinary(in);
		addRecord(rec);
	}
}

void InsertLog::commit(CdbTransactionManager* trxManager) {
	{
		WriteLockHandle* lockH = trxManager->databaseWriteLock();
		StackDbLockUnlocker unlocker(lockH);

		RecordObjectIdPublisher* publisher = trxManager->getRecordObjectIdPublisher();

		int maxLoop = this->records.size();
		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* rec = this->records.get(i);
			uint64_t oid = publisher->newOid();

			CdbOid oidObj(oid);

			rec->setOid(&oidObj);
		}

		publisher->saveSchema();

		trxManager->commitInsert(this);
	}
}

void InsertLog::addRecord(CdbRecord* record) noexcept {
	this->records.addElement(record);
}

void InsertLog::setTable(CdbTableIdentifier* table) noexcept {
	this->table = table;
}

const ArrayList<CdbRecord>* InsertLog::getRecords() const noexcept {
	return &this->records;
}


} /* namespace codablecash */
