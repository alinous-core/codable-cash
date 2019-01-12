/*
 * TransactionIdIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionIdIndex.h"
#include "btreekey/BtreeKeyFactory.h"
#include "mempool/FeeIndex.h"
#include "mempool/FeeValueFactory.h"
#include "base/UnicodeString.h"
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

bool TransactionIdIndex::exists() const noexcept {
	UnicodeString fileName(TransactionIdIndex::FILE_NAME);
	Btree btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new FeeValueFactory());

	return btree.exists();
}

void TransactionIdIndex::create() noexcept(false) {
}

void TransactionIdIndex::open() noexcept(false) {
}

void TransactionIdIndex::close() noexcept {
}

} /* namespace codablecash */
