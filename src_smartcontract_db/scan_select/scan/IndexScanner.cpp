/*
 * IndexScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan_select/scan/IndexScanner.h"

#include "schema_table/record/table_record_key/AbstractCdbKey.h"

#include "schema_table/table_store/IndexStore.h"

#include "btree/Btree.h"
#include "btree/BtreeScanner.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_value/CdbOidValueList.h"
#include "schema_table/record/table_record_value/CdbOidValueListCursor.h"

#include "schema_table/record/table_record_key/CdbRecordKey.h"
namespace codablecash {

IndexScanner::IndexScanner(const CdbRecordKey* begin, bool beginEq, const CdbRecordKey* end, bool endEq, IndexStore* store)
			: RangeChecker(begin, beginEq, end, endEq) {
	this->store = store;
	this->scanner = nullptr;
	this->cursor = nullptr;
	this->nextObj = nullptr;
}

IndexScanner::~IndexScanner() {
	shutdown();
}

void IndexScanner::start() {
	Btree* btree = this->store->getBtree();
	this->scanner = btree->getScanner();

	AbstractBtreeKey* first = getFirstScanKey();
	this->scanner->begin(first);
}

void IndexScanner::shutdown() noexcept {
	if(this->scanner != nullptr){
		delete this->scanner;
		this->scanner = nullptr;
		delete this->cursor;
		this->cursor = nullptr;
		this->nextObj = nullptr;
	}
}

bool IndexScanner::hasNext() {
	return __hasNext();
}

bool IndexScanner::__hasNext() {
	while(this->cursor == nullptr || !this->cursor->hasNext()){
		if(this->scanner->hasNext()){
			delete this->cursor;
			this->cursor = nullptr;

			const AbstractBtreeKey* key = this->scanner->nextKey();
			const CdbRecordKey* recordKey = dynamic_cast<const CdbRecordKey*>(key);
			if(!checkLowerBound(recordKey)){
				continue;
			}
			if(!checkUpperBound(recordKey)){
				return false;
			}

			const IBlockObject* obj = this->scanner->next();
			const CdbOidValueList* list = dynamic_cast<const CdbOidValueList*>(obj);

			this->cursor = new CdbOidValueListCursor(list);
			this->cursor->hasNext(); // load next
		}
		else{
			return false;
		}
	}

	this->nextObj = this->cursor->next();

	return true;
}

const CdbOid* IndexScanner::next() {
	return this->nextObj;
}

} /* namespace codablecash */
