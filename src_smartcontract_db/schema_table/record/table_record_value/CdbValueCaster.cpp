/*
 * String2CdbValue.cpp
 *
 *  Created on: 2020/09/22
 *      Author: iizuka
 */

#include "schema_table/record/table_record_value/CdbValueCaster.h"

#include "engine/CdbException.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"
#include "schema_table/record/table_record_value/CdbStringValue.h"
#include "schema_table/record/table_record_value/CdbByteValue.h"
#include "schema_table/record/table_record_value/CdbShortValue.h"
#include "schema_table/record/table_record_value/CdbIntValue.h"
#include "schema_table/record/table_record_value/CdbLongValue.h"

#include "base/Long.h"
#include "base/Integer.h"
#include "base/UnicodeString.h"

#include "schema_table/record/table_record_value/CdbValueCastException.h"

#include "base/StackRelease.h"

using alinous::Integer;
using alinous::Long;

namespace codablecash {

AbstractCdbValue* CdbValueCaster::cast(const AbstractCdbValue* value, uint8_t cdbValueType) {
	if(value == nullptr){
		return nullptr;
	}

	uint8_t type = value->getType();

	AbstractCdbValue* ret = nullptr;

	switch(type){
	case  AbstractCdbValue::TYPE_BYTE:
	{
		const CdbByteValue* v = dynamic_cast<const CdbByteValue*>(value);
		ret = castFromByte(v, cdbValueType);
		break;
	}
	case  AbstractCdbValue::TYPE_SHORT:
	{
		const CdbShortValue* v = dynamic_cast<const CdbShortValue*>(value);
		ret = castFromShort(v, cdbValueType);
		break;
	}
	case  AbstractCdbValue::TYPE_INT:
	{
		const CdbIntValue* v = dynamic_cast<const CdbIntValue*>(value);
		ret = castFromInt(v, cdbValueType);
		break;
	}
	case  AbstractCdbValue::TYPE_LONG:
	{
		const CdbLongValue* v = dynamic_cast<const CdbLongValue*>(value);
		ret = castFromLong(v, cdbValueType);
		break;
	}
	case  AbstractCdbValue::TYPE_STRING:
	{
		const CdbStringValue* v = dynamic_cast<const CdbStringValue*>(value);
		ret = castFromString(v, cdbValueType);
		break;
	}
	default:
		throw new CdbException(L"Failed in casting value", __FILE__, __LINE__);
	}

	return ret;
}

AbstractCdbValue* CdbValueCaster::castFromString(const CdbStringValue* value, uint8_t cdbValueType) {
	const UnicodeString* str = value->getValue();
	return convertFromString(str, cdbValueType);
}

AbstractCdbValue* CdbValueCaster::castFromByte(const CdbByteValue* value, uint8_t cdbValueType) {
	int8_t v = value->getValue();

	AbstractCdbValue* ret = nullptr;
	switch(cdbValueType){

	case AbstractCdbValue::TYPE_BYTE:
		ret = new CdbByteValue(v);
		break;
	case  AbstractCdbValue::TYPE_SHORT:
		ret = new CdbShortValue((int16_t)v);
		break;
	case AbstractCdbValue::TYPE_INT:
		ret = new CdbIntValue((int32_t)v);
		break;
	case AbstractCdbValue::TYPE_LONG:
		ret = new CdbLongValue((int64_t)v);
		break;
	case AbstractCdbValue::TYPE_STRING:
	default:
		ret = toString(v);
		break;
	}

	return ret;
}

AbstractCdbValue* CdbValueCaster::castFromShort(const CdbShortValue* value, uint8_t cdbValueType) {
	int16_t v = value->getValue();

	AbstractCdbValue* ret = nullptr;
	switch(cdbValueType){
	case  AbstractCdbValue::TYPE_BYTE:
		ret = new CdbByteValue(v);
		break;
	case  AbstractCdbValue::TYPE_SHORT:
		ret = new CdbShortValue((int16_t)v);
		break;
	case  AbstractCdbValue::TYPE_INT:
		ret = new CdbIntValue((int32_t)v);
		break;
	case  AbstractCdbValue::TYPE_LONG:
		ret = new CdbLongValue((int64_t)v);
		break;
	case  AbstractCdbValue::TYPE_STRING:
	default:
		ret = toString(v);
		break;
	}

	return ret;
}

AbstractCdbValue* CdbValueCaster::castFromInt(const CdbIntValue* value,	uint8_t cdbValueType) {
	int32_t v = value->getValue();

	AbstractCdbValue* ret = nullptr;
	switch(cdbValueType){
	case  AbstractCdbValue::TYPE_BYTE:
		ret = new CdbByteValue(v);
		break;
	case  AbstractCdbValue::TYPE_SHORT:
		ret = new CdbShortValue((int16_t)v);
		break;
	case  AbstractCdbValue::TYPE_INT:
		ret = new CdbIntValue((int32_t)v);
		break;
	case  AbstractCdbValue::TYPE_LONG:
		ret = new CdbLongValue((int64_t)v);
		break;
	case  AbstractCdbValue::TYPE_STRING:
	default:
		ret = toString(v);
		break;
	}

	return ret;
}

AbstractCdbValue* CdbValueCaster::castFromLong(const CdbLongValue* value, uint8_t cdbValueType) {
	int32_t v = value->getValue();

	AbstractCdbValue* ret = nullptr;
	switch(cdbValueType){
	case  AbstractCdbValue::TYPE_BYTE:
		ret = new CdbByteValue(v);
		break;
	case  AbstractCdbValue::TYPE_SHORT:
		ret = new CdbShortValue((int16_t)v);
		break;
	case  AbstractCdbValue::TYPE_INT:
		ret = new CdbIntValue((int32_t)v);
		break;
	case  AbstractCdbValue::TYPE_LONG:
		ret = new CdbLongValue((int64_t)v);
		break;
	case  AbstractCdbValue::TYPE_STRING:
	default:
		ret = toString(v);
		break;
	}

	return ret;
}

CdbStringValue* CdbValueCaster::toString(int64_t value) {
	UnicodeString* str = Long::toString(value, 10); __STP(str);

	return new CdbStringValue(str);
}

AbstractCdbValue* CdbValueCaster::convertFromString(const UnicodeString* str, uint8_t cdbValueType) {
	if(str == nullptr){
		return nullptr;
	}

	AbstractCdbValue* ret = nullptr;

	switch(cdbValueType){
	case  AbstractCdbValue::TYPE_BYTE:
		ret = stringToCdbByteValue(str);
		break;
	case  AbstractCdbValue::TYPE_SHORT:
		ret = stringToCdbShortValue(str);
		break;
	case  AbstractCdbValue::TYPE_INT:
		ret = stringToCdbIntValue(str);
		break;
	case  AbstractCdbValue::TYPE_LONG:
		ret = stringToCdbLongValue(str);
		break;
	case  AbstractCdbValue::TYPE_STRING:
		ret = stringToCdbStringValue(str);
		break;
	default:
		throw new CdbException(L"Wrong cdb value type", __FILE__, __LINE__);
	}

	return ret;
}

CdbStringValue* CdbValueCaster::stringToCdbStringValue(const UnicodeString* str) {
	return new CdbStringValue(str);
}

CdbByteValue* CdbValueCaster::stringToCdbByteValue(const UnicodeString* str) {
	int64_t value = Long::parseLong(str);
	if(value < CdbValueCaster::MIN_BYTE_VALUE || value > CdbValueCaster::MAX_BYTE_VALUE){
		throw new CdbValueCastException(L"Can not cast string value to byte value", __FILE__, __LINE__);
	}

	return new CdbByteValue((int8_t)value);
}

CdbShortValue* CdbValueCaster::stringToCdbShortValue(const UnicodeString* str) {
	int64_t value = Long::parseLong(str);
	if(value < CdbValueCaster::MIN_SHORT_VALUE || value > CdbValueCaster::MAX_SHORT_VALUE){
		throw new CdbValueCastException(L"Can not cast string value to short value", __FILE__, __LINE__);
	}

	return new CdbShortValue((int16_t)value);
}

CdbIntValue* CdbValueCaster::stringToCdbIntValue(const UnicodeString* str) {
	int64_t value = Long::parseLong(str);
	if(value < Integer::MIN_VALUE || value > Integer::MAX_VALUE){
		throw new CdbValueCastException(L"Can not cast string value to int value", __FILE__, __LINE__);
	}

	return new CdbIntValue((int32_t)value);
}

CdbLongValue* CdbValueCaster::stringToCdbLongValue(const UnicodeString* str) {
	int64_t value = Long::parseLong(str);

	return new CdbLongValue(value);
}

AbstractCdbValue* CdbValueCaster::getDefaultValue(uint8_t cdbValueType) {
	AbstractCdbValue* ret = nullptr;

	switch(cdbValueType){
	case  AbstractCdbValue::TYPE_BYTE:
		ret = new CdbByteValue(0);
		break;
	case  AbstractCdbValue::TYPE_SHORT:
		ret = new CdbShortValue(0);
		break;
	case  AbstractCdbValue::TYPE_INT:
		ret = new CdbIntValue(0);
		break;
	case  AbstractCdbValue::TYPE_LONG:
		ret = new CdbLongValue(0);
		break;
	case  AbstractCdbValue::TYPE_STRING:
		ret = new CdbStringValue(L"");
		break;
	default:
		throw new CdbException(L"Wrong cdb value type", __FILE__, __LINE__);
	}

	return ret;
}


} /* namespace codablecash */
