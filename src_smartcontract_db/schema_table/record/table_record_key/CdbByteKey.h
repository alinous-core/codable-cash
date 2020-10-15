/*
 * CdbByteKey.h
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_CDBBYTEKEY_H_
#define TABLE_RECORD_KEY_CDBBYTEKEY_H_

#include "schema_table/record/table_record_key/AbstractCdbKey.h"

namespace codablecash {

class CdbByteKey : public AbstractCdbKey {
public:
	CdbByteKey(const CdbByteKey& inst);
	CdbByteKey();
	explicit CdbByteKey(int8_t value);
	virtual ~CdbByteKey();

	virtual AbstractBtreeKey* clone()  const noexcept;
	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	int8_t getValue() const noexcept {
		return value;
	}

private:
	int8_t value;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_CDBBYTEKEY_H_ */
