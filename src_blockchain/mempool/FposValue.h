/*
 * FposValue.h
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#ifndef MEMPOOL_FPOSVALUE_H_
#define MEMPOOL_FPOSVALUE_H_

#include <inttypes.h>
#include "filestore_block/IBlockObject.h"

namespace codablecash {
using namespace alinous;

class FposValue : public IBlockObject{
public:
	explicit FposValue(uint64_t fpos);
	virtual ~FposValue();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static FposValue* fromBinary(ByteBuffer* in);

private:
	uint64_t fpos;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FPOSVALUE_H_ */
