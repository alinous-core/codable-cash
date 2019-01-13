/*
 * FeeIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include <mempool/IndexValueFactory.h>
#include "btreekey/BtreeKeyFactory.h"
#include "mempool/FeeIndex.h"
#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "btree/Btree.h"
#include "btree/BtreeConfig.h"

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
	Btree btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new IndexValueFactory());

	bool ex = btree.exists();

	return ex;
}

void FeeIndex::create() noexcept(false) {
	UnicodeString fileName(FeeIndex::FILE_NAME);
	Btree btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new IndexValueFactory());

	BtreeConfig config;
	config.nodeNumber = 8;
	config.blockSize = 256;
	btree.create(&config);
}

void FeeIndex::open() noexcept(false) {
	UnicodeString fileName(FeeIndex::FILE_NAME);
	this->btree = new Btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new IndexValueFactory());

	BtreeOpenConfig opconf;
	opconf.numDataBuffer = 256;
	opconf.numNodeBuffer = 512;
	this->btree->open(&opconf);
}

void FeeIndex::close() noexcept {
	this->btree->close();
}

} /* namespace codablecash */
