/*
 * AbstractSwapCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/AbstractSwapCache.h"

#include "random_access_file/DiskCacheManager.h"

#include "base/UnicodeString.h"

#include "btree/BtreeConfig.h"
#include "btree/Btree.h"

namespace codablecash {

AbstractSwapCache::AbstractSwapCache(const UnicodeString* name,BtreeKeyFactory* keyFactory,
		AbstractBtreeDataFactory* dataFactory, DiskCacheManager* diskCache) {
	this->name = new UnicodeString(name);

	this->keyFactory = keyFactory;
	this->dataFactory = dataFactory;
	this->diskCache = diskCache;

	this->currentSize = 0;
	this->swappiness = 100;
	this->useDisk = false;

	this->btreeConfig = new BtreeConfig();

	this->btree = nullptr;
}

AbstractSwapCache::~AbstractSwapCache() {
	delete this->name;

	this->keyFactory = nullptr;
	this->dataFactory = nullptr;
	this->diskCache = nullptr;

	delete this->btree;
	delete this->btreeConfig;
}

void AbstractSwapCache::putData(const AbstractBtreeKey* key, const IBlockObject* data) {
}

const IBlockObject* AbstractSwapCache::findData(const AbstractBtreeKey* key) {


}

} /* namespace codablecash */
