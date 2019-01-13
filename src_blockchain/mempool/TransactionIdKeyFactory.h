/*
 * TransactionIdKeyFactory.h
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONIDKEYFACTORY_H_
#define MEMPOOL_TRANSACTIONIDKEYFACTORY_H_

#include "btreekey/BtreeKeyFactory.h"

namespace alinous {
class AbstractBtreeKey;
}

namespace codablecash {
using namespace alinous;

class TransactionIdKeyFactory : public BtreeKeyFactory {
public:
	static const constexpr uint32_t TRX_ID_KEY{0x03};

	TransactionIdKeyFactory();
	virtual ~TransactionIdKeyFactory();

	virtual AbstractBtreeKey* fromBinary(uint32_t keyType, ByteBuffer* in) const;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONIDKEYFACTORY_H_ */
