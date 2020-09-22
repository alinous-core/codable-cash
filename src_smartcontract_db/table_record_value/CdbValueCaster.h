/*
 * String2CdbValue.h
 *
 *  Created on: 2020/09/22
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBVALUECASTER_H_
#define TABLE_RECORD_VALUE_CDBVALUECASTER_H_
#include <cstdint>

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbValue;
class CdbStringValue;
class CdbByteValue;
class CdbShortValue;
class CdbIntValue;
class CdbLongValue;

class CdbValueCaster {
public:
	constexpr static const int64_t MAX_BYTE_VALUE{(int64_t)((int8_t)0x7F)};
	constexpr static const int64_t MIN_BYTE_VALUE{(int64_t)((int8_t)0x80)};
	constexpr static const int64_t MAX_SHORT_VALUE{(int64_t)((int16_t)0x7FFF)};
	constexpr static const int64_t MIN_SHORT_VALUE{(int64_t)((int16_t)0x8000)};

	AbstractCdbValue* cast(const AbstractCdbValue* value, uint8_t cdbValueType);
	AbstractCdbValue* convertFromString(const UnicodeString* str, uint8_t cdbValueType);

private:
	AbstractCdbValue* castFromString(const CdbStringValue* value, uint8_t cdbValueType);
	AbstractCdbValue* castFromByte(const CdbByteValue* value, uint8_t cdbValueType);
	AbstractCdbValue* castFromShort(const CdbShortValue* value, uint8_t cdbValueType);
	AbstractCdbValue* castFromInt(const CdbIntValue* value, uint8_t cdbValueType);
	AbstractCdbValue* castFromLong(const CdbLongValue* value, uint8_t cdbValueType);

	CdbStringValue* toString(int64_t value);

	CdbStringValue* stringToCdbStringValue(const UnicodeString* str);
	CdbByteValue* stringToCdbByteValue(const UnicodeString* str);
	CdbShortValue* stringToCdbShortValue(const UnicodeString* str);
	CdbIntValue* stringToCdbIntValue(const UnicodeString* str);
	CdbLongValue* stringToCdbLongValue(const UnicodeString* str);
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBVALUECASTER_H_ */
