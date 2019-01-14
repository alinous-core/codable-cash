/*
 * TransactionStore.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionStore.h"
#include "mempool/TransactionRecord.h"

#include "bc_base/AbstractTransaction.h"

#include "base_io/File.h"
#include "base_io/ByteBuffer.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"
#include "filestore_block/BlockFileStore.h"
#include "filestore_block/BlockHandle.h"


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
	File hf = getStoreHeaderFile();

	bool fb = f.exists();
	bool hfb = hf.exists();

	return fb && hfb;
}

void TransactionStore::open() noexcept(false){
	UnicodeString fileName(TransactionStore::FILE_NAME);
	UnicodeString* dir = this->baseDir->getAbsolutePath();
	StackRelease<UnicodeString> __st_dir(dir);

	this->store = new BlockFileStore(dir, &fileName, this->cacheManager);

	this->store->open(false);
}

void TransactionStore::close() noexcept {
	this->store->close();
}

File TransactionStore::getStoreFile() const noexcept {
	UnicodeString binFileName(TransactionStore::FILE_NAME);
	binFileName.append(L".bin");

	File* f = this->baseDir->get(&binFileName);
	StackRelease<File> __st_f(f);

	return *f;
}

uint64_t TransactionStore::storeTransaction(const TransactionRecord* record) {
	int size = record->binarySize();

	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true);
	StackRelease<ByteBuffer> __st_buff(buff);
	record->toBinary(buff);

	buff->position(0);

	BlockHandle* handle = this->store->alloc(size);
	StackRelease<BlockHandle> __st_handle(handle);

	assert(buff->capacity() == size);

	handle->write((const char*)buff->array(), size);

	uint64_t fpos = handle->getFpos();
	return fpos;
}

File TransactionStore::getStoreHeaderFile() const noexcept {
	UnicodeString binFileName(TransactionStore::FILE_NAME);
	binFileName.append(L"-header.bin");

	File* f = this->baseDir->get(&binFileName);
	StackRelease<File> __st_f(f);

	return *f;
}

void TransactionStore::create() noexcept(false) {
	UnicodeString fileName(TransactionStore::FILE_NAME);
	UnicodeString* dir = this->baseDir->getAbsolutePath();
	StackRelease<UnicodeString> __st_dir(dir);

	BlockFileStore tmpStore(dir, &fileName, this->cacheManager);
	tmpStore.createStore(true, 1024);
}

TransactionRecord* TransactionStore::loadRecord(uint64_t fpos) {
	BlockHandle* handle = this->store->get(fpos);
	StackRelease<BlockHandle> __st_handle(handle);

	ByteBuffer* buff = handle->getBuffer();

	TransactionRecord* rec = TransactionRecord::fromBinary(buff);
	return rec;
}

} /* namespace codablecash */
