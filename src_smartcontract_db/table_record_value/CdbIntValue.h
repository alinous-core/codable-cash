/*
 * CdbIntValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBINTVALUE_H_
#define TABLE_RECORD_VALUE_CDBINTVALUE_H_

#include "table_record_value/AbstractCdbValue.h"

namespace codablecash {

class CdbIntValue : public AbstractCdbValue {
public:
	CdbIntValue(const CdbIntValue& inst);
	CdbIntValue();
	virtual ~CdbIntValue();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

private:
	int32_t value;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBINTVALUE_H_ */
