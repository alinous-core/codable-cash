/*
 * TransactionIdIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include <mempool/IndexValueFactory.h>
#include "mempool/TransactionIdIndex.h"
#include "btreekey/BtreeKeyFactory.h"
#include "mempool/FeeIndex.h"
#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "btree/Btree.h"
#include "btree/BtreeConfig.h"

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
	Btree btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new IndexValueFactory());

	bool ex = btree.exists();

	return ex;
}

void TransactionIdIndex::create() noexcept(false) {
	UnicodeString fileName(TransactionIdIndex::FILE_NAME);
	Btree btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new IndexValueFactory());

	BtreeConfig config;
	config.nodeNumber = 8;
	config.blockSize = 256;
	btree.create(&config);
}

void TransactionIdIndex::open() noexcept(false) {
	UnicodeString fileName(TransactionIdIndex::FILE_NAME);
	this->btree = new Btree(this->baseDir, &fileName, this->cacheManager, new BtreeKeyFactory(), new IndexValueFactory());

	BtreeOpenConfig opconf;
	opconf.numDataBuffer = 256;
	opconf.numNodeBuffer = 512;
	this->btree->open(&opconf);
}

void TransactionIdIndex::close() noexcept {
	this->btree->close();
}

} /* namespace codablecash */
