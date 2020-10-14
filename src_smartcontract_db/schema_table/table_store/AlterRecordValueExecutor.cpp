/*
 * AlterRecordValueExecutor.cpp
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#include <cstdint>

#include "schema_table/table_store/AlterRecordValueExecutor.h"

#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_value/CdbValueCaster.h"

#include "schema_table/table_store/TableStore.h"
#include "schema_table/table_store/RecordStore.h"

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

	AbstractCdbValue* defaultValue = CdbValueCaster::convertFromString(defstr, cdbType); __STP(defaultValue);

	RecordStore* recordStore = store->getRecordStore();
	Btree* btree = recordStore->getBtree();
	BtreeScanner* scanner = btree->getScanner(); __STP(scanner);

	scanner->begin();

	while(scanner->hasNext()){
		const IBlockObject* obj = scanner->next();
		CdbRecord* record = dynamic_cast<CdbRecord*>(obj->copyData()); __STP(record);

		record->addValue(defaultValue != nullptr ? defaultValue->copy() : nullptr);
		recordStore->insert(record);
	}
}

void AlterRecordValueExecutor::removeColumn(TableStore* store) {
	RecordStore* recordStore = store->getRecordStore();
	Btree* btree = recordStore->getBtree();
	BtreeScanner* scanner = btree->getScanner(); __STP(scanner);

	int removePosition = this->column->getPosition();

	scanner->begin();
	while(scanner->hasNext()){
		const IBlockObject* obj = scanner->next();
		CdbRecord* record = dynamic_cast<CdbRecord*>(obj->copyData()); __STP(record);

		record->removeColumnValue(removePosition);

		recordStore->insert(record);
	}
}

} /* namespace codablecash */
