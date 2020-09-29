/*
 * InsertRecordsCacheCursor.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "transaction_update_cache/InsertRecordsCacheCursor.h"
#include "transaction_update_cache/InsertedRecordsRepository.h"

#include "btree/IBtreeScanner.h"

#include "table_record/CdbRecord.h"

namespace codablecash {

InsertRecordsCacheCursor::InsertRecordsCacheCursor(InsertedRecordsRepository* insertsRepo) {
	this->scanner = insertsRepo->getScanner();
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
