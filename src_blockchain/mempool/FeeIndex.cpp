/*
 * FeeIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include <btreekey/BtreeKeyFactory.h>
#include "mempool/FeeIndex.h"
#include "mempool/FeeValueFactory.h"
#include "base/UnicodeString.h"
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

bool FeeIndex::exists() const noexcept {
	UnicodeString fileName(FeeIndex::FILE_NAME);
	Btree btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new FeeValueFactory());

	return btree.exists();
}

void FeeIndex::create() noexcept(false) {
}

void FeeIndex::open() noexcept(false) {
}

void FeeIndex::close() noexcept {
}

} /* namespace codablecash */
