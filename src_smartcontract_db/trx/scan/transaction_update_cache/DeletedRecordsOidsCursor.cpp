/*
 * DeletedRecordsOidsCursor.cpp
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#include <cassert>

#include "trx/scan/transaction_update_cache/DeletedRecordsOidsCursor.h"
#include "trx/scan/transaction_update_cache/DeletedOidsRepository.h"

#include "engine/CdbOid.h"

#include "btree/IBtreeScanner.h"

#include "filestore_block/IBlockObject.h"

#include "schema_table/record/table_record_value/CdbOidValueList.h"

namespace codablecash {

DeletedRecordsOidsCursor::DeletedRecordsOidsCursor(DeletedOidsRepository* repo) {
	this->scanner = repo->getScanner();
	this->scanner->begin();
}

DeletedRecordsOidsCursor::~DeletedRecordsOidsCursor() {
	delete this->scanner;
}

bool DeletedRecordsOidsCursor::hasNext() const noexcept {
	return this->scanner->hasNext();
}

const CdbOid* DeletedRecordsOidsCursor::next() noexcept {
	const IBlockObject* obj = this->scanner->next();
	const CdbOidValueList* vlist =  dynamic_cast<const CdbOidValueList*>(obj);
	assert(vlist != nullptr);


	const CdbOid* recordOid = dynamic_cast<const CdbOid*>(vlist->get(0));
	assert(recordOid != nullptr);

	return recordOid;
}

} /* namespace codablecash */
