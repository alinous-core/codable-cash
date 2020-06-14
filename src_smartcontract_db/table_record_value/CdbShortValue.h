/*
 * CdbShortValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBSHORTVALUE_H_
#define TABLE_RECORD_VALUE_CDBSHORTVALUE_H_

#include "table_record_value/AbstractCdbValue.h"

namespace codablecash {

class CdbShortValue : public AbstractCdbValue {
public:
	CdbShortValue(const CdbShortValue& inst);
	CdbShortValue();
	virtual ~CdbShortValue();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractCdbValue* copy() const noexcept;
	virtual AbstractCdbKey* toKey() const noexcept;

	int16_t getValue() const noexcept {
		return this->value;
	}
private:
	int16_t value;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBSHORTVALUE_H_ */
