/*
 * MemPool.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */


#include "mempool/MemPool.h"
#include "mempool/TransactionStore.h"
#include "mempool/TransactionIdIndex.h"
#include "mempool/FeeIndex.h"
#include "mempool/TransactionRecord.h"

#include "bc_base/Transaction.h"

#include "base/UnicodeString.h"
#include "base_io/File.h"
#include "random_access_file/DiskCacheManager.h"
#include "base_thread/ConcurrentGate.h"

#include "btree/Btree.h"
#include "btreekey/BtreeKeyFactory.h"
#include "osenv/funcs.h"

namespace codablecash {

MemPool::MemPool(const File* baseDir) {
	this->baseDir = new File(*baseDir);
	this->cacheManager = new DiskCacheManager(Os::getSystemPageSize() * 4 * 4);
	this->store = nullptr;
	this->feeIndex = nullptr;
	this->trxIdIndex = nullptr;
	this->rwLock = new ConcurrentGate();
}


MemPool::MemPool(const File* baseDir, int cacheBytes) {
	this->baseDir = new File(*baseDir);
	this->cacheManager = new DiskCacheManager(cacheBytes);
	this->store = nullptr;
	this->feeIndex = nullptr;
	this->trxIdIndex = nullptr;
	this->rwLock = new ConcurrentGate();
}


MemPool::~MemPool() {
	delete this->baseDir;
	if(this->cacheManager != nullptr){
		delete this->cacheManager;
	}

	if(this->store != nullptr){
		delete this->store;
	}
	if(this->feeIndex != nullptr){
		delete this->feeIndex;
	}
	if(this->trxIdIndex != nullptr){
		delete this->trxIdIndex;
	}
	delete this->rwLock;
}

void MemPool::init() {
	this->store = new TransactionStore(this->baseDir, this->cacheManager);
	this->feeIndex = new FeeIndex(this->baseDir, this->cacheManager);
	this->trxIdIndex = new TransactionIdIndex(this->baseDir, this->cacheManager);

	if(!this->store->exists() || !this->feeIndex->exists() || !this->trxIdIndex->exists()){
		this->store->create();
		this->feeIndex->create();
		this->trxIdIndex->create();
	}

	this->store->open();
	this->feeIndex->open();
	this->trxIdIndex->open();
}

void MemPool::close() {
	this->store->close();
	this->feeIndex->close();
	this->trxIdIndex->close();
}

void MemPool::addTransaction(const AbstractTransaction* trx) {
	StackWriteLock __lock(this->rwLock);

	TransactionRecord record(trx);

	uint64_t fpos = this->store->storeTransaction(&record);

	const TransactionId* trxId = record.getTrx()->getTransactionId();
	this->trxIdIndex->addIndex(trxId, fpos);

	const BalanceUnit* fee = record.getTrx()->getFee();
	this->feeIndex->addIndex(fee, fpos);
}

} /* namespace codablecash */
