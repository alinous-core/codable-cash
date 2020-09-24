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

	static AbstractCdbValue* cast(const AbstractCdbValue* value, uint8_t cdbValueType);
	static AbstractCdbValue* convertFromString(const UnicodeString* str, uint8_t cdbValueType);
	static AbstractCdbValue* getDefaultValue(uint8_t cdbValueType);

private:
	static AbstractCdbValue* castFromString(const CdbStringValue* value, uint8_t cdbValueType);
	static AbstractCdbValue* castFromByte(const CdbByteValue* value, uint8_t cdbValueType);
	static AbstractCdbValue* castFromShort(const CdbShortValue* value, uint8_t cdbValueType);
	static AbstractCdbValue* castFromInt(const CdbIntValue* value, uint8_t cdbValueType);
	static AbstractCdbValue* castFromLong(const CdbLongValue* value, uint8_t cdbValueType);

	static CdbStringValue* toString(int64_t value);

	static CdbStringValue* stringToCdbStringValue(const UnicodeString* str);
	static CdbByteValue* stringToCdbByteValue(const UnicodeString* str);
	static CdbShortValue* stringToCdbShortValue(const UnicodeString* str);
	static CdbIntValue* stringToCdbIntValue(const UnicodeString* str);
	static CdbLongValue* stringToCdbLongValue(const UnicodeString* str);
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBVALUECASTER_H_ */
