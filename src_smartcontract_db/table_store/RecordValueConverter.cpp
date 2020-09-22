/*
 * RecordValueConverter.cpp
 *
 *  Created on: 2020/09/21
 *      Author: iizuka
 */

#include "table_store/RecordValueConverter.h"

#include "table_record/CdbRecord.h"

#include "table/CdbTableColumn.h"

#include "table_record_value/CdbValueCaster.h"
#include "table_record_value/CdbStringValue.h"
#include "table_record_value/AbstractCdbValue.h"

#include "base/Exception.h"


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

	AbstractCdbValue* newValue = getModifiedValue(lastValue);

	newRecord->setValue(newValue, pos);

	return newRecord;
}

AbstractCdbValue* RecordValueConverter::getModifiedValue(const AbstractCdbValue* lastValue) {
	if(lastValue == nullptr){
		return handleNullValue();
	}

	uint8_t lastCdbType = lastValue->getType();
	uint8_t cdbType = this->column->getType();
	if(cdbType == AbstractCdbValue::TYPE_STRING && lastCdbType == AbstractCdbValue::TYPE_STRING){
		return handleStringType(lastValue);
	}

	AbstractCdbValue* ret = nullptr;
	try{
		ret = CdbValueCaster::cast(lastValue, cdbType);
	}
	catch(Exception* e){
		delete e;
		ret = CdbValueCaster::getDefaultValue(cdbType);
	}

	return ret;
}

AbstractCdbValue* RecordValueConverter::handleNullValue() {
	bool isnotnull = this->column->isNotnull();
	if(!isnotnull){
		return nullptr;
	}

	uint8_t cdbType = this->column->getType();

	return CdbValueCaster::getDefaultValue(cdbType);
}

AbstractCdbValue* RecordValueConverter::handleStringType(const AbstractCdbValue* lastValue) {
	const CdbStringValue* lastStringValue = dynamic_cast<const CdbStringValue*>(lastValue);

	int length = this->column->getLength();
	if(length <= 0){
		return lastStringValue->copy();
	}

	return lastStringValue->limitStringLength(length);
}

} /* namespace codablecash */
