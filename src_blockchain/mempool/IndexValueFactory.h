/*
 * FeeValueFactory.h
 *
 *  Created on: 2019/01/06
 *      Author: iizuka
 */

#ifndef MEMPOOL_INDEXVALUEFACTORY_H_
#define MEMPOOL_INDEXVALUEFACTORY_H_

#include "btree/AbstractBtreeDataFactory.h"

namespace codablecash {
using namespace alinous;

class IndexValueFactory : public AbstractBtreeDataFactory{
public:
	IndexValueFactory();
	virtual ~IndexValueFactory();

	virtual IBlockObject* makeDataFromBinary(ByteBuffer* in);
};

} /* namespace codablecash */

#endif /* MEMPOOL_INDEXVALUEFACTORY_H_ */
