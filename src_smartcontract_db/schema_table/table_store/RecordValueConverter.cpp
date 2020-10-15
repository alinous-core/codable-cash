/*
 * RecordValueConverter.cpp
 *
 *  Created on: 2020/09/21
 *      Author: iizuka
 */

#include "schema_table/table_store/RecordValueConverter.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/record/table_record_value/CdbValueCaster.h"
#include "schema_table/record/table_record_value/CdbStringValue.h"
#include "schema_table/record/table_record_value/AbstractCdbValue.h"

#include "base/Exception.h"


namespace codablecash {

RecordValueConverter::RecordValueConverter(CdbTableColumn* column, const AbstractCdbValue* defaultValue) {
	this->pos = column->getPosition();
	this->isnotnull = column->isNotnull();
	this->cdbType = column->getType();
	this->length = column->getLength();

	this->defaultValue = defaultValue;
}

RecordValueConverter::RecordValueConverter(int pos, bool isnotnull,
				uint8_t cdbType, int length, const AbstractCdbValue* defaultValue) {
	this->pos = pos;
	this->isnotnull = isnotnull;
	this->cdbType = cdbType;
	this->length = length;

	this->defaultValue = defaultValue;
}

RecordValueConverter::~RecordValueConverter() {

}

CdbRecord* RecordValueConverter::processUpdate(const CdbRecord* record) {
	AbstractCdbValue* obj = record->copy();
	CdbRecord* newRecord = dynamic_cast<CdbRecord*>(obj);

	const AbstractCdbValue* lastValue = newRecord->get(this->pos);

	AbstractCdbValue* newValue = getModifiedValue(lastValue);

	newRecord->setValue(newValue, this->pos);

	return newRecord;
}

AbstractCdbValue* RecordValueConverter::getModifiedValue(const AbstractCdbValue* lastValue) {
	if(lastValue == nullptr){
		return handleNullValue();
	}

	uint8_t lastCdbType = lastValue->getType();
	if(this->cdbType == AbstractCdbValue::TYPE_STRING && lastCdbType == AbstractCdbValue::TYPE_STRING){
		return handleStringType(lastValue);
	}

	AbstractCdbValue* ret = nullptr;
	try{
		ret = CdbValueCaster::cast(lastValue, this->cdbType);
	}
	catch(Exception* e){
		delete e;
		ret = CdbValueCaster::getDefaultValue(this->cdbType);
	}

	return ret;
}

AbstractCdbValue* RecordValueConverter::handleNullValue() {
	if(!this->isnotnull){
		return nullptr;
	}

	if(this->defaultValue != nullptr){
		return this->defaultValue->copy();
	}

	return CdbValueCaster::getDefaultValue(this->cdbType);
}

AbstractCdbValue* RecordValueConverter::handleStringType(const AbstractCdbValue* lastValue) {
	const CdbStringValue* lastStringValue = dynamic_cast<const CdbStringValue*>(lastValue);

	if(this->length <= 0){
		return lastStringValue->copy();
	}

	return lastStringValue->limitStringLength(length);
}

} /* namespace codablecash */
