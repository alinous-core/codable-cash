/*
 * AbstractSwapCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/AbstractSwapCache.h"

#include "random_access_file/DiskCacheManager.h"

#include "base/UnicodeString.h"

namespace codablecash {

AbstractSwapCache::AbstractSwapCache(const UnicodeString* name,BtreeKeyFactory* keyFactory,
		AbstractBtreeDataFactory* dataFactory, DiskCacheManager* diskCache) {
	this->name = new UnicodeString(name);

	this->keyFactory = keyFactory;
	this->dataFactory = dataFactory;
	this->diskCache = diskCache;

	this->currentSize = 0;
}

AbstractSwapCache::~AbstractSwapCache() {
	delete this->name;

	this->keyFactory = nullptr;
	this->dataFactory = nullptr;
	this->diskCache = nullptr;
}

} /* namespace codablecash */
