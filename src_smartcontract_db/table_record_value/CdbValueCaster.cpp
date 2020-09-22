/*
 * String2CdbValue.cpp
 *
 *  Created on: 2020/09/22
 *      Author: iizuka
 */

#include "table_record_value/CdbValueCaster.h"

#include "engine/CdbException.h"

#include "table_record_value/AbstractCdbValue.h"
#include "table_record_value/CdbStringValue.h"
#include "table_record_value/CdbByteValue.h"
#include "table_record_value/CdbShortValue.h"
#include "table_record_value/CdbIntValue.h"
#include "table_record_value/CdbLongValue.h"

#include "base/Long.h"
#include "base/Integer.h"

#include "table_record_value/CdbValueCastException.h"

using alinous::Integer;
using alinous::Long;

namespace codablecash {

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

} /* namespace codablecash */
