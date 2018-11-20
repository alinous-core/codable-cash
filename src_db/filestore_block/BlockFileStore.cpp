/*
 * BlockFileStore.cpp
 *
 *  Created on: 2018/10/06
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "filestore_block/BlockFileStore.h"

#include "filestore_block/BlockFileHeader.h"
#include "filestore_block/BlockFileBody.h"
#include "filestore_block/BlockHandle.h"

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

void BlockFileStore::createStore(bool del, uint64_t defaultSize) {
	createStore(del, defaultSize, 256);
}

void BlockFileStore::createStore(bool del, uint64_t defaultSize, uint64_t blockSize) noexcept(false) {
	ERROR_POINT(L"BlockFileStore::createStore")

	FileStore::createStore(del, defaultSize);

	FileStore::open(true);

	this->header = new BlockFileHeader(this->headerFile);
	this->body = new BlockFileBody(this->file);

	try{
		this->header->createStore(del, defaultSize, blockSize);
		this->body->createStore(del, blockSize);
	}
	catch(Exception* e){
		internalClear();
		FileStore::close();

		throw new BlockFileStorageException(L"Failed in creating block file store", e, __FILE__, __LINE__);
	}

	internalClear();
	FileStore::close();
}

void BlockFileStore::open(bool sync) noexcept(false) {
	ERROR_POINT(L"BlockFileStore::open")

	FileStore::open(sync);

	this->header = new BlockFileHeader(this->headerFile);
	this->body = new BlockFileBody(this->file);

	try{
		this->header->loadFromFile();
	}
	catch(Exception* e){
		internalClear();
		FileStore::close();

		throw new BlockFileStorageException(L"Failed in opening block file store", e, __FILE__, __LINE__);
	}
}


bool BlockFileStore::isOpened() const noexcept {
	return FileStore::isOpened();
}

void BlockFileStore::close() noexcept {
	internalClear();

	FileStore::close();
}

BlockHandle* BlockFileStore::alloc(uint64_t size) {
	BlockHandle* handle = new BlockHandle(this);

	try{
		uint64_t pos = this->header->alloc();
		handle->current = pos;
		handle->start = pos;

	}
	catch(Exception* e){
		internalClear();
		FileStore::close();

		throw new BlockFileStorageException(L"Failed in allocating block", e, __FILE__, __LINE__);
	}

	return handle;
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


