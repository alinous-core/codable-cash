/*
 * SingleKeyOidCache.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_SINGLEKEYOIDCACHE_H_
#define TRANSACTION_CACHE_SINGLEKEYOIDCACHE_H_

#include "transaction_cache/AbstractSwapCache.h"

namespace codablecash {

class SingleKeyOidCache : public AbstractSwapCache {
public:
	SingleKeyOidCache();
	virtual ~SingleKeyOidCache();
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_SINGLEKEYOIDCACHE_H_ */
