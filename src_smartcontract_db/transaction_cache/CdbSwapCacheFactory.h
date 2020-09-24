/*
 * CdbSwapCacheFactory.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_CDBSWAPCACHEFACTORY_H_
#define TRANSACTION_CACHE_CDBSWAPCACHEFACTORY_H_

#include "transaction_cache/SwapCacheFactory.h"

namespace codablecash {

class CdbKeyFactory;
class CdbDataFactory;

class CdbSwapCacheFactory: public SwapCacheFactory {
public:
	CdbSwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache);
	virtual ~CdbSwapCacheFactory();
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_CDBSWAPCACHEFACTORY_H_ */
