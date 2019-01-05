/*
 * TransactionIdIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionIdIndex.h"
#include "base_io/File.h"
#include "btree/Btree.h"

namespace codablecash {

TransactionIdIndex::TransactionIdIndex(File* baseDir, DiskCacheManager* cacheManager) {
	this->baseDir = new File(*baseDir);
	this->cacheManager = cacheManager;
	this->btree = nullptr;
}

TransactionIdIndex::~TransactionIdIndex() {
	delete this->baseDir;
	if(this->btree != nullptr){
		delete this->btree;
	}
}

} /* namespace codablecash */
