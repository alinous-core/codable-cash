/*
 * SingleKeyOidCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/SingleKeyOidCache.h"

namespace codablecash {

SingleKeyOidCache::SingleKeyOidCache(CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory)
			: AbstractSwapCache(keyFactory, dataFactory) {

}

SingleKeyOidCache::~SingleKeyOidCache() {

}

} /* namespace codablecash */
