/*
 * InsertRecordsCacheCursor.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "trx/scan/transaction_update_cache/InsertRecordsCacheCursor.h"
#include "trx/scan/transaction_update_cache/InsertedRecordsRepository.h"

#include "btree/IBtreeScanner.h"

#include "schema_table/record/table_record/CdbRecord.h"

namespace codablecash {

InsertRecordsCacheCursor::InsertRecordsCacheCursor(InsertedRecordsRepository* insertsRepo) {
	this->scanner = insertsRepo->getScanner();
	this->scanner->begin();
}

InsertRecordsCacheCursor::~InsertRecordsCacheCursor() {
	delete this->scanner;
}

bool InsertRecordsCacheCursor::hasNext() const noexcept {
	return this->scanner->hasNext();
}

const CdbRecord* InsertRecordsCacheCursor::next() noexcept {
	const IBlockObject* obj = this->scanner->next();

	return dynamic_cast<const CdbRecord*>(obj);
}

} /* namespace codablecash */
