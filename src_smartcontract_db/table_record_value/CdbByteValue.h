/*
 * CdbByteValue.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_VALUE_CDBBYTEVALUE_H_
#define TABLE_RECORD_VALUE_CDBBYTEVALUE_H_

#include "table_record_value/AbstractCdbValue.h"
#include <cstdlib>

namespace codablecash {

class CdbByteValue : public AbstractCdbValue {
public:
	CdbByteValue(const CdbByteValue& inst);
	CdbByteValue();
	virtual ~CdbByteValue();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

private:
	int8_t value;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_VALUE_CDBBYTEVALUE_H_ */
