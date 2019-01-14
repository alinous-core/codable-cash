/*
 * FeeTransactionsListValue.h
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#ifndef MEMPOOL_FEETRANSACTIONSLISTVALUE_H_
#define MEMPOOL_FEETRANSACTIONSLISTVALUE_H_

#include <inttypes.h>
#include "filestore_block/IBlockObject.h"
#include "base/RawArrayPrimitive.h"

namespace codablecash {
using namespace alinous;

class FeeTransactionsListValue : public IBlockObject {
public:
	FeeTransactionsListValue();
	explicit FeeTransactionsListValue(uint64_t value);
	virtual ~FeeTransactionsListValue();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static FeeTransactionsListValue* fromBinary(ByteBuffer* in);

	void join(const FeeTransactionsListValue* value) noexcept;
	bool contains(uint64_t value) const noexcept;
	void remove(uint64_t value) noexcept;
	int indexof(uint64_t value) const noexcept;

	bool isEmpty() const noexcept;
private:
	RawArrayPrimitive<uint64_t> list;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEETRANSACTIONSLISTVALUE_H_ */
