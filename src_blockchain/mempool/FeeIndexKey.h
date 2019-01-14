/*
 * FeeIndexKey.h
 *
 *  Created on: 2019/01/14
 *      Author: iizuka
 */

#ifndef MEMPOOL_FEEINDEXKEY_H_
#define MEMPOOL_FEEINDEXKEY_H_

#include "btree/AbstractBtreeKey.h"
#include <inttypes.h>

namespace codablecash {
using namespace alinous;

class FeeIndexKey : public AbstractBtreeKey {
public:
	explicit FeeIndexKey(uint64_t value);
	FeeIndexKey(uint64_t value, uint64_t fpos);
	virtual ~FeeIndexKey();

	virtual bool isInfinity() const { return false; }

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static FeeIndexKey* fromBinary(ByteBuffer* in);

	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;
	virtual AbstractBtreeKey* clone() const noexcept;

protected:
	uint64_t value;
	uint64_t fpos;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEEINDEXKEY_H_ */
