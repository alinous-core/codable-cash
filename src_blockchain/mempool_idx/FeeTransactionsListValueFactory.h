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
	virtual void registerData(const AbstractBtreeKey* key, const IBlockObject* data, DataNode* dataNode, BtreeStorage* store) const;
	virtual bool beforeRemove(DataNode* dataNode, BtreeStorage* store, const AbstractBtreeKey* key) const;

	AbstractBtreeDataFactory* copy() const noexcept;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEETRANSACTIONSLISTVALUEFACTORY_H_ */
