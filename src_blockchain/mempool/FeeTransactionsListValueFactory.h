/*
 * FeeTransactionsListValueFactory.h
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#ifndef MEMPOOL_FEETRANSACTIONSLISTVALUEFACTORY_H_
#define MEMPOOL_FEETRANSACTIONSLISTVALUEFACTORY_H_

#include "btree/AbstractBtreeDataFactory.h"

namespace codablecash {
using namespace alinous;

class FeeTransactionsListValueFactory  : public AbstractBtreeDataFactory {
public:
	FeeTransactionsListValueFactory();
	virtual ~FeeTransactionsListValueFactory();

	virtual IBlockObject* makeDataFromBinary(ByteBuffer* in);
	virtual void registerData(const IBlockObject* data, DataNode* dataNode, BtreeStorage* store) const;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEETRANSACTIONSLISTVALUEFACTORY_H_ */
