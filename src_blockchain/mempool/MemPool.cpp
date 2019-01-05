/*
 * MemPool.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/MemPool.h"
#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "random_access_file/DiskCacheManager.h"

#include "btree/Btree.h"
#include "btreekey/BTreeKeyFactory.h"

namespace codablecash {

MemPool::MemPool(File* baseDir) {
	this->baseDir = new File(*baseDir);
	this->cacheManager = nullptr;
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
	UnicodeString name(L"membool");

}

void MemPool::close() {
}

} /* namespace codablecash */
