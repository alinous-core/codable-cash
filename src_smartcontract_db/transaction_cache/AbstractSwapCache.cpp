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

#include "btree_memory/BtreeOnMemory.h"

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

	this->btreeConfig = nullptr;
	this->memoryBtree = nullptr;

	this->btree = nullptr;
}

AbstractSwapCache::~AbstractSwapCache() {
	delete this->name;

	this->keyFactory = nullptr;
	this->dataFactory = nullptr;
	this->diskCache = nullptr;

	delete this->memoryBtree;
	delete this->btree;
	delete this->btreeConfig;
}

void AbstractSwapCache::init(uint64_t nodeNumber) {
	this->btreeConfig = new BtreeConfig();
	this->btreeConfig->nodeNumber = nodeNumber;

	this->memoryBtree = new BtreeOnMemory(this->btreeConfig, this->keyFactory);
}

void AbstractSwapCache::putData(const AbstractBtreeKey* key, const IBlockObject* data) {
}



const IBlockObject* AbstractSwapCache::findData(const AbstractBtreeKey* key) {


}

} /* namespace codablecash */
