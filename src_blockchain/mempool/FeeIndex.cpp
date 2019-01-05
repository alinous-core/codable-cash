/*
 * FeeIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/FeeIndex.h"
#include "base_io/File.h"
#include "btree/Btree.h"

namespace codablecash {

FeeIndex::FeeIndex(const File* baseDir, DiskCacheManager* cacheManager) {
	this->baseDir = new File(*baseDir);
	this->cacheManager = cacheManager;
	this->btree = nullptr;
}

FeeIndex::~FeeIndex() {
	delete this->baseDir;
	if(this->btree != nullptr){
		delete this->btree;
	}
}

} /* namespace codablecash */
