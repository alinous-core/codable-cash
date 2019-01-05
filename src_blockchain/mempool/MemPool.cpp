/*
 * MemPool.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/MemPool.h"
#include "mempool/TransactionStore.h"
#include "mempool/TransactionIdIndex.h"
#include "mempool/FeeIndex.h"

#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "random_access_file/DiskCacheManager.h"

#include "btree/Btree.h"
#include "btreekey/BTreeKeyFactory.h"

namespace codablecash {

MemPool::MemPool(File* baseDir) {
	this->baseDir = new File(*baseDir);
	this->cacheManager = new DiskCacheManager(1024 * 2);
	this->store = nullptr;
	this->index = nullptr;
	this->trxIdIndex = nullptr;
}

MemPool::~MemPool() {
	delete this->baseDir;
	if(this->cacheManager != nullptr){
		delete this->cacheManager;
	}

	if(this->store != nullptr){
		delete this->store;
	}
	if(this->index != nullptr){
		delete this->index;
	}
	if(this->trxIdIndex != nullptr){
		delete this->trxIdIndex;
	}
}

void MemPool::init() {
	this->store = new TransactionStore(this->baseDir, this->cacheManager);
	this->index = new FeeIndex(this->baseDir, this->cacheManager);
	this->trxIdIndex = new TransactionIdIndex(this->baseDir, this->cacheManager);

	if(!this->store->exists()){
		this->store->create();
	}

	this->store->open();
}

void MemPool::close() {
	this->store->close();
}

} /* namespace codablecash */
