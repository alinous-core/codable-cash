/*
 * TransactionStore.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionStore.h"
#include "base_io/File.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "filestore_block/BlockFileStore.h"



namespace codablecash {

TransactionStore::TransactionStore(const File* baseDir, DiskCacheManager* cacheManager) {
	this->baseDir = new File(*baseDir);
	this->cacheManager = cacheManager;
	this->store = nullptr;
}

TransactionStore::~TransactionStore() {
	delete this->baseDir;
	if(this->store != nullptr){
		delete this->store;
	}
}

bool TransactionStore::exists() const noexcept {
	File f = getStoreFile();
	return f.exists();
}

void TransactionStore::open() noexcept(false){
	this->store->open(false);
}

void TransactionStore::close() noexcept {
	this->store->close();
}

File TransactionStore::getStoreFile() const noexcept {
	File* f = this->baseDir->get(TransactionStore::FILE_NAME);
	StackRelease<File> __st_f(f);

	return *f;
}

void TransactionStore::create() noexcept(false) {
	UnicodeString fileName(TransactionStore::FILE_NAME);
	UnicodeString* dir = this->baseDir->getAbsolutePath();
	StackRelease<UnicodeString> __st_dir(dir);

	this->store = new BlockFileStore(dir, &fileName, this->cacheManager);
	this->store->createStore(true, 1024);
}

} /* namespace codablecash */
