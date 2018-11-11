/*
 * BlockFileStore.cpp
 *
 *  Created on: 2018/10/06
 *      Author: iizuka
 */

#include "filestore_block/BlockFileStore.h"

#include "filestore_block/BlockFileHeader.h"
#include "filestore_block/BlockFileBody.h"

#include "exceptions.h"

namespace alinous {

BlockFileStore::BlockFileStore(UnicodeString* dir, UnicodeString* name, DiskCacheManager* cacheManager) noexcept
	: FileStore(dir, name, cacheManager)
{
	this->header = nullptr;
	this->body = nullptr;
}

BlockFileStore::~BlockFileStore() noexcept {
	close();
}

void BlockFileStore::createStore(bool del, uint64_t defaultSize) noexcept(false) {
	FileStore::createStore(del, defaultSize);

	this->header = new BlockFileHeader(this->headerFile);
	this->body = new BlockFileBody(this->file);

	try{
		this->header->createStore(del);
		this->body->createStore(del);
	}
	catch(Exception* e){
		internalClear();

		throw new BlockFileStorageException(L"", e, __FILE__, __LINE__);
	}

	internalClear();
}


bool BlockFileStore::isOpened() const noexcept {
	return FileStore::isOpened();
}

void BlockFileStore::close() noexcept {
	internalClear();

	FileStore::close();
}

void BlockFileStore::internalClear() noexcept {
	if(this->header){
		delete this->header;
		this->header = nullptr;
	}
	if(this->body){
		delete this->body;
		this->body = nullptr;
	}
}

} /* namespace alinous */

