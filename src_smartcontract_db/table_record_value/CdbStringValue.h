/*
 * CdbStringValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBSTRINGVALUE_H_
#define TABLE_RECORD_VALUE_CDBSTRINGVALUE_H_

#include "table_record_value/AbstractCdbValue.h"



namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class CdbStringValue : public AbstractCdbValue {
public:
	CdbStringValue(const CdbStringValue& inst);

	CdbStringValue();
	virtual ~CdbStringValue();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	static int stringSize(UnicodeString* str) noexcept;
	static void putString(ByteBuffer* out, UnicodeString* str) noexcept;
	static UnicodeString* getString(ByteBuffer* in) noexcept;
private:
	UnicodeString* value;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBSTRINGVALUE_H_ */
