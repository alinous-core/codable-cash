/*
 * AlterRecordValueExecutor.cpp
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#include <cstdint>

#include "table_store/AlterRecordValueExecutor.h"

#include "table/CdbTableColumn.h"

#include "table_record/CdbRecord.h"

#include "table_record_value/CdbValueCaster.h"

#include "table_store/TableStore.h"
#include "table_store/RecordStore.h"

#include "btree/Btree.h"
#include "btree/BtreeScanner.h"

#include "base/StackRelease.h"

namespace codablecash {

AlterRecordValueExecutor::AlterRecordValueExecutor(const CdbTableColumn* column) {
	this->column = column;
}

AlterRecordValueExecutor::~AlterRecordValueExecutor() {
	this->column = nullptr;
}

void AlterRecordValueExecutor::addColumn(TableStore* store) {
	uint8_t cdbType = this->column->getType();
	const UnicodeString* defstr = this->column->getDefaultValue();

	AbstractCdbValue* defaultValue = CdbValueCaster::convertFromString(defstr, cdbType);

	Btree* btree = store->getRecordStore()->getBtree();
	BtreeScanner* scanner = btree->getScanner(); __STP(scanner);

	scanner->begin();

	while(scanner->hasNext()){
		const IBlockObject* obj = scanner->next();
		CdbRecord* record = dynamic_cast<CdbRecord*>(obj->copyData());

	}

	// TODO AlterRecordValueExecutor::addNewColumn
}

void AlterRecordValueExecutor::removeColumn(TableStore* store) {
	Btree* btree = store->getRecordStore()->getBtree();
	BtreeScanner* scanner = btree->getScanner(); __STP(scanner);

	scanner->begin();
	while(scanner->hasNext()){
		const IBlockObject* obj = scanner->next();
		CdbRecord* record = dynamic_cast<CdbRecord*>(obj->copyData());

	}

	// TODO AlterRecordValueExecutor::removeColumn
}

} /* namespace codablecash */
