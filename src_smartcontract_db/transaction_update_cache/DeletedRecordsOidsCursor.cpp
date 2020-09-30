/*
 * DeletedRecordsOidsCursor.cpp
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#include <cassert>

#include "transaction_update_cache/DeletedRecordsOidsCursor.h"
#include "transaction_update_cache/DeletedOidsRepository.h"

#include "engine/CdbOid.h"

#include "btree/IBtreeScanner.h"

#include "filestore_block/IBlockObject.h"


namespace codablecash {

DeletedRecordsOidsCursor::DeletedRecordsOidsCursor(DeletedOidsRepository* repo) {
	this->scanner = repo->getScanner();
}

DeletedRecordsOidsCursor::~DeletedRecordsOidsCursor() {
	delete this->scanner;
}

bool DeletedRecordsOidsCursor::hasNext() const noexcept {
	return this->scanner->hasNext();
}

const CdbOid* DeletedRecordsOidsCursor::next() noexcept {
	const IBlockObject* obj = this->scanner->next();
	const CdbOid* recordOid = dynamic_cast<const CdbOid*>(obj);

	assert(recordOid != nullptr);

	return recordOid;
}

} /* namespace codablecash */
