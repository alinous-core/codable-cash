/*
 * CdbIntKey.h
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_CDBINTKEY_H_
#define TABLE_RECORD_KEY_CDBINTKEY_H_

#include "table_record_key/AbstractCdbKey.h"

namespace codablecash {

class CdbIntKey : public AbstractCdbKey {
public:
	CdbIntKey();
	virtual ~CdbIntKey();

	virtual AbstractBtreeKey* clone()  const noexcept;
	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

private:
	int32_t value;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_CDBINTKEY_H_ */
