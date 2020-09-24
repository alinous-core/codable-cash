/*
 * TransactionIdIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionIdIndex.h"
#include "mempool/IndexValueFactory.h"
#include "mempool/TransactionIdKeyFactory.h"
#include "mempool/TransactionIdKey.h"
#include "mempool_idx/FeeIndex.h"
#include "mempool/FposValue.h"

#include "bc_base/TransactionId.h"

#include "btreekey/BtreeKeyFactory.h"

#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "btree/Btree.h"
#include "btree/BtreeConfig.h"

#include "base/StackRelease.h"

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
	Btree btree(this->baseDir, &fileName, this->cacheManager, new TransactionIdKeyFactory(), new IndexValueFactory());

	bool ex = btree.exists();

	return ex;
}

void TransactionIdIndex::create() noexcept(false) {
	UnicodeString fileName(TransactionIdIndex::FILE_NAME);
	Btree btree(this->baseDir, &fileName, this->cacheManager, new TransactionIdKeyFactory(), new IndexValueFactory());

	BtreeConfig config;
	config.nodeNumber = 8;
	config.blockSize = 256;
	btree.create(&config);
}

void TransactionIdIndex::open() noexcept(false) {
	UnicodeString fileName(TransactionIdIndex::FILE_NAME);
	this->btree = new Btree(this->baseDir, &fileName, this->cacheManager, new TransactionIdKeyFactory(), new IndexValueFactory());

	BtreeOpenConfig opconf;
	opconf.numDataBuffer = 256;
	opconf.numNodeBuffer = 512;
	this->btree->open(&opconf);
}

void TransactionIdIndex::close() noexcept {
	this->btree->close();
}

void TransactionIdIndex::addIndex(const TransactionId* trxId, uint64_t fpos) {
	TransactionIdKey key(trxId);
	FposValue value(fpos);

	this->btree->putData(&key, &value);
}

uint64_t TransactionIdIndex::findbyTransactionId(const TransactionId* trxId) const {
	TransactionIdKey key(trxId);

	IBlockObject* obj = this->btree->findByKey(&key);
	if(obj == nullptr){
		return 0;
	}

	StackRelease<IBlockObject> __st_obj(obj);
	FposValue* fposValue = dynamic_cast<FposValue*>(obj);
	return fposValue->getFpos();
}

void codablecash::TransactionIdIndex::removeTransaction(const TransactionId* trxId) {
	TransactionIdKey key(trxId);

	this->btree->remove(&key);
}

} /* namespace codablecash */
