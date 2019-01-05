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

MemPool::MemPool(File* file) {
	this->file = new File(*file);
	this->mainStore = nullptr;
	this->cacheManager = nullptr;
	this->keyFactory = new BTreeKeyFactory();
}

MemPool::~MemPool() {
	delete this->file;
	if(this->mainStore != nullptr){
		delete this->mainStore;
	}
	if(this->cacheManager != nullptr){
		delete this->cacheManager;
	}
	delete this->keyFactory;
}

void MemPool::init() {
	UnicodeString name(L"membool");

}

void MemPool::close() {
}

} /* namespace codablecash */
