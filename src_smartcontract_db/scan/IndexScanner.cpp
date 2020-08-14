/*
 * IndexScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan/IndexScanner.h"

#include "table_record_key/AbstractCdbKey.h"

#include "table_store/IndexStore.h"

#include "btree/Btree.h"
#include "btree/BtreeScanner.h"

#include "table_record/CdbRecord.h"

#include "table_record_value/CdbOidValueList.h"

namespace codablecash {

IndexScanner::IndexScanner(AbstractCdbKey* begin, bool beginEq, AbstractCdbKey* end, bool endEq, IndexStore* store)
			: RangeScanner(begin, beginEq, end, endEq) {
	this->store = store;
	this->scanner = nullptr;
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
	}
}

bool IndexScanner::hasNext() {


	return this->scanner->hasNext();
}

const CdbRecord* IndexScanner::next() {
	const IBlockObject* obj = this->scanner->next();
	const CdbOidValueList* oidList = dynamic_cast<const CdbOidValueList*>(obj);

	return nullptr; // FIXME index
}

} /* namespace codablecash */
