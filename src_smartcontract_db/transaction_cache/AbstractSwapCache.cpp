/*
 * AbstractSwapCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/AbstractSwapCache.h"

#include "random_access_file/DiskCacheManager.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "btree/BtreeConfig.h"
#include "btree/Btree.h"

#include "btree_memory/BtreeOnMemory.h"

#include "btree_memory/MemoryBtreeScanner.h"

#include "base_io/File.h"

namespace codablecash {

AbstractSwapCache::AbstractSwapCache(const File* folder, const UnicodeString* name,BtreeKeyFactory* keyFactory,
		AbstractBtreeDataFactory* dataFactory, DiskCacheManager* diskCache) {
	this->folder = new File(*folder);
	this->name = new UnicodeString(name);

	this->keyFactory = keyFactory;
	this->dataFactory = dataFactory;
	this->diskCache = diskCache;

	this->currentSize = 0;
	this->swappiness = 100;
	this->useDisk = false;

	this->memoryBtree = nullptr;

	this->btree = nullptr;

	this->current = nullptr;
}

AbstractSwapCache::~AbstractSwapCache() {
	this->keyFactory = nullptr;
	this->dataFactory = nullptr;
	this->diskCache = nullptr;

	delete this->memoryBtree;

	if(this->btree != nullptr){
		this->btree->close();
	}
	delete this->btree;

	removeFiles();

	delete this->folder;
	delete this->name;
}

void AbstractSwapCache::removeFiles() noexcept {
	Btree::clearFiles(this->folder, this->name);
}

void AbstractSwapCache::init(uint64_t nodeNumber) {
	BtreeConfig* btreeConfig = new BtreeConfig();
	btreeConfig->nodeNumber = nodeNumber;

	this->memoryBtree = new BtreeOnMemory(btreeConfig, this->keyFactory);
}

void AbstractSwapCache::putData(const AbstractBtreeKey* key, const IBlockObject* data) {
	if(!this->useDisk){
		putDataIntoMemory(key, data);
	}
	else{
		putDataIntoDisk(key, data);
	}
}

void AbstractSwapCache::putDataIntoMemory(const AbstractBtreeKey* key, const IBlockObject* data) {
	this->memoryBtree->putData(key, data);
}

void AbstractSwapCache::putDataIntoDisk(const AbstractBtreeKey* key, const IBlockObject* data) {
	this->btree->putData(key, data);
}

void AbstractSwapCache::swapIfNecessary() {
	if(!this->useDisk && this->currentSize > this->swappiness){
		swapToDisk();
	}
}

void AbstractSwapCache::swapToDisk() {
	this->btree = new Btree(this->folder, this->name, this->diskCache, this->keyFactory, this->dataFactory);

	const BtreeConfig* config = this->memoryBtree->getConfig();
	this->btree->create(config);


	BtreeOpenConfig opconf;
	this->btree->open(&opconf);

	{
		MemoryBtreeScanner* scanner = this->memoryBtree->getScanner(); __STP(scanner);
		scanner->begin();

		while(scanner->hasNext()){
			const IBlockObject* obj = scanner->next();
			const AbstractBtreeKey* key = scanner->nextKey();

			this->btree->putData(key, obj);
		}

		delete this->memoryBtree;
		this->memoryBtree = nullptr;
	}

	this->useDisk = true;
}

const IBlockObject* AbstractSwapCache::findData(const AbstractBtreeKey* key) {
	if(!this->useDisk){
		return findDataFromMemory(key);
	}

	return findDataFromDisk(key);
}

const IBlockObject* AbstractSwapCache::findDataFromMemory(const AbstractBtreeKey* key) {
	const IBlockObject* obj = this->memoryBtree->findByKey(key);
	return obj;
}

const IBlockObject* AbstractSwapCache::findDataFromDisk(const AbstractBtreeKey* key) {
	IBlockObject* obj = this->btree->findByKey(key);
	setCurrent(obj);

	return obj;
}

void AbstractSwapCache::setCurrent(IBlockObject* obj) noexcept {
	delete this->current;
	this->current = obj;
}

} /* namespace codablecash */
