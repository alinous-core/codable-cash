/*
 * AbstractSwapCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/AbstractSwapCache.h"

namespace codablecash {

AbstractSwapCache::AbstractSwapCache(CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory) {
	this->keyFactory = keyFactory;
	this->dataFactory = dataFactory;
	this->currentSize = 0;
}

AbstractSwapCache::~AbstractSwapCache() {
	this->keyFactory = nullptr;
	this->dataFactory = nullptr;
}

} /* namespace codablecash */
