/*
 * FeeValueFactory.h
 *
 *  Created on: 2019/01/06
 *      Author: iizuka
 */

#ifndef MEMPOOL_FEEVALUEFACTORY_H_
#define MEMPOOL_FEEVALUEFACTORY_H_

#include "btree/AbstractBtreeDataFactory.h"

namespace codablecash {
using namespace alinous;

class FeeValueFactory : public AbstractBtreeDataFactory{
public:
	FeeValueFactory();
	virtual ~FeeValueFactory();

	virtual IBlockObject* makeDataFromBinary(ByteBuffer* in);
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEEVALUEFACTORY_H_ */
