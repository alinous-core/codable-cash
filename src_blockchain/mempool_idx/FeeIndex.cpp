/*
 * FeeIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool_idx/FeeIndex.h"
#include "mempool_idx/FeeTransactionsListValueFactory.h"
#include "mempool_idx/FeeTransactionsListValue.h"

#include "mempool_idx/FeeIndexKey.h"
#include "mempool_idx/FeeIndexKeyFactory.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "base_io/File.h"

#include "bc_base/BalanceUnit.h"

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

	FeeIndexKeyFactory* keyFactory = new FeeIndexKeyFactory(); __STP(keyFactory);
	FeeTransactionsListValueFactory* dataFactory = new FeeTransactionsListValueFactory(); __STP(dataFactory);

	Btree btree(this->baseDir, &fileName, this->cacheManager, keyFactory, dataFactory);

	bool ex = btree.exists();

	return ex;
}

void FeeIndex::create() noexcept(false) {
	UnicodeString fileName(FeeIndex::FILE_NAME);

	FeeIndexKeyFactory* keyFactory = new FeeIndexKeyFactory(); __STP(keyFactory);
	FeeTransactionsListValueFactory* dataFactory = new FeeTransactionsListValueFactory(); __STP(dataFactory);

	Btree btree(this->baseDir, &fileName, this->cacheManager, keyFactory, dataFactory);

	BtreeConfig config;
	config.nodeNumber = 8;
	config.blockSize = 256;
	btree.create(&config);
}

void FeeIndex::open() noexcept(false) {
	UnicodeString fileName(FeeIndex::FILE_NAME);

	FeeIndexKeyFactory* keyFactory = new FeeIndexKeyFactory(); __STP(keyFactory);
	FeeTransactionsListValueFactory* dataFactory = new FeeTransactionsListValueFactory(); __STP(dataFactory);

	this->btree = new Btree(this->baseDir, &fileName, this->cacheManager, keyFactory, dataFactory);

	BtreeOpenConfig opconf;
	opconf.numDataBuffer = 256;
	opconf.numNodeBuffer = 512;
	this->btree->open(&opconf);
}

void FeeIndex::close() noexcept {
	this->btree->close();
}

void FeeIndex::addIndex(const BalanceUnit* fee, uint64_t fpos) {
	FeeIndexKey key(fee->getAmount());
	FeeTransactionsListValue value(fpos);

	this->btree->putData(&key, &value);
}

void FeeIndex::removeIndex(const BalanceUnit* fee, uint64_t fpos) {
	FeeIndexKey key(fee->getAmount(), fpos);

	this->btree->remove(&key);
}


} /* namespace codablecash */
