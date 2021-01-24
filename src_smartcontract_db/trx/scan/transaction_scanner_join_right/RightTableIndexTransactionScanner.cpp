/*
 * RightTableIndexTransactionScanner.cpp
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableIndexTransactionScanner.h"

#include "schema_table/table/CdbTableIndex.h"
#include "schema_table/table/CdbTable.h"

#include "schema_table/table_store/TableStore.h"
#include "schema_table/table_store/IndexStore.h"
#include "schema_table/table_store/CdbStorageManager.h"

#include "schema_table/record/table_record_key/CdbRecordKey.h"

#include "trx/transaction/CdbTransaction.h"
#include "trx/transaction/CdbTransactionManager.h"

#include "scan_select/scan/IndexScanner.h"

namespace codablecash {

RightTableIndexTransactionScanner::RightTableIndexTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx,
		const CdbTable* table, const AbstractScanCondition* filterCondition, CdbTableIndex* index)
			: AbstractTransactionScanner(metadata, trx, table, filterCondition){
	this->index = index;
	this->indexStore = nullptr;
	this->scanner = nullptr;
}

RightTableIndexTransactionScanner::~RightTableIndexTransactionScanner() {
	shutdown();

	this->index = nullptr;
}

void RightTableIndexTransactionScanner::start() {
	CdbTransactionManager* mgr = this->trx->getTrxManager();
	CdbStorageManager* storageManager = mgr->getStorageManager();

	const CdbOid* oid = this->table->getOid();
	TableStore* tableStore = storageManager->getTableStore(oid);

	const CdbOid* indexOid = this->index->getOid();
	this->indexStore = tableStore->getIndexStore(indexOid);

}

void RightTableIndexTransactionScanner::reset(const AbstractCdbKey* key) {
	const CdbRecordKey* rkey = dynamic_cast<const CdbRecordKey*>(key);

	IndexScanner* s = this->indexStore->getScanner(rkey, true, rkey, true);
	setScanner(s);
}

bool RightTableIndexTransactionScanner::hasNext() {
	return false;
}

const CdbRecord* RightTableIndexTransactionScanner::next() {
	return nullptr;
}

void RightTableIndexTransactionScanner::shutdown() {
	setScanner(nullptr);
}

void RightTableIndexTransactionScanner::setScanner(IndexScanner* scanner) noexcept {
	if(this->scanner != nullptr){
		this->scanner->shutdown();
		delete this->scanner;
	}

	this->scanner = scanner;
}

} /* namespace codablecash */
