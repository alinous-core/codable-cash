/*
 * RecordValueConverter.cpp
 *
 *  Created on: 2020/09/21
 *      Author: iizuka
 */

#include "table_store/RecordValueConverter.h"

#include "table_record_value/AbstractCdbValue.h"

#include "table_record/CdbRecord.h"

#include "table/CdbTableColumn.h"

namespace codablecash {

RecordValueConverter::RecordValueConverter(CdbTableColumn* column, const AbstractCdbValue* defaultValue) {
	this->column = column;
	this->defaultValue = defaultValue;
}

RecordValueConverter::~RecordValueConverter() {
	this->column = nullptr;

}

CdbRecord* RecordValueConverter::processUpdate(const CdbRecord* record) {
	AbstractCdbValue* obj = record->copy();
	CdbRecord* newRecord = dynamic_cast<CdbRecord*>(obj);

	int pos = this->column->getPosition();
	const AbstractCdbValue* lastValue = newRecord->get(pos);



	return newRecord;
}

} /* namespace codablecash */
