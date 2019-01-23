/*
 * FeeIndexKeyFactory.h
 *
 *  Created on: 2019/01/14
 *      Author: iizuka
 */

#ifndef MEMPOOL_FEEINDEXKEYFACTORY_H_
#define MEMPOOL_FEEINDEXKEYFACTORY_H_

#include "btreekey/BtreeKeyFactory.h"

namespace codablecash {
using namespace alinous;

class FeeIndexKeyFactory : public BtreeKeyFactory {
public:
	static const constexpr uint32_t FEE_INDEX_KEY{0x14};

	FeeIndexKeyFactory();
	virtual ~FeeIndexKeyFactory();

	virtual AbstractBtreeKey* fromBinary(uint32_t keyType, ByteBuffer* in) const;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEEINDEXKEYFACTORY_H_ */
