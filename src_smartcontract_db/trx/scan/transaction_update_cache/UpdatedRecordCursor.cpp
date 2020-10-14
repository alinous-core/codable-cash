/*
 * UpdatedRecordCursor.cpp
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#include <cassert>

#include "trx/scan/transaction_update_cache/UpdatedRecordCursor.h"
#include "trx/scan/transaction_update_cache/UpdatedRecordsRepository.h"

#include "btree/IBtreeScanner.h"

#include "schema_table/record/table_record/CdbRecord.h"

namespace codablecash {

UpdatedRecordCursor::UpdatedRecordCursor(UpdatedRecordsRepository* repo) {
	this->scanner = repo->getScanner();
	this->scanner->begin();
}

UpdatedRecordCursor::~UpdatedRecordCursor() {
	delete this->scanner;
}

bool UpdatedRecordCursor::hasNext() const noexcept {
	return this->scanner->hasNext();
}

const CdbRecord* UpdatedRecordCursor::next() noexcept {
	const IBlockObject* obj = this->scanner->next();
	const CdbRecord* record = dynamic_cast<const CdbRecord*>(obj);

	assert(record != nullptr);

	return record;
}

} /* namespace codablecash */
