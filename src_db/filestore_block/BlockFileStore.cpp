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
#include "filestore_block/BlockData.h"

#include "base/ArrayList.h"

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


	try{
		this->header->createStore(del, defaultSize, blockSize);

		this->body = new BlockFileBody(this->file, this->header->getBlockSize());
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


	try{
		this->header->loadFromFile();
		this->body = new BlockFileBody(this->file, this->header->getBlockSize());
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
	ERROR_POINT(L"BlockFileStore::alloc")

	BlockHandle* handle = new BlockHandle(this);

	try{
		internalAllocBody(handle, size);
	}
	catch(Exception* e){
		delete handle;

		internalClear();
		FileStore::close();

		throw new BlockFileStorageException(L"Failed in allocating block", e, __FILE__, __LINE__);
	}

	return handle;
}

typedef struct __block_alloc_t {
	uint16_t used;
	uint64_t fpos;
	uint64_t nextfpos;
} block_alloc_t;


void BlockFileStore::internalAllocBody(BlockHandle* handle, const uint64_t size) {
	uint64_t blockDataSize = this->body->getBlockSize() - BlockData::HEADER_SIZE;

	int allocBlocks = size / blockDataSize;
	int mod = size % blockDataSize;
	if(mod != 0){
		allocBlocks++;
	}

	ArrayList<block_alloc_t> list;
	list.setDeleteOnExit();

	uint64_t sizeRemain = size;
	for(int i = 0; i != allocBlocks; ++i){
		block_alloc_t* block = new block_alloc_t;
		list.addElement(block);

		uint64_t pos = this->header->alloc();
		block->fpos = pos * this->body->getBlockSize(); // block No starts with 1

		block->used = (blockDataSize < sizeRemain) ? blockDataSize : sizeRemain;

		sizeRemain -= block->used;
	}

	for(int i = 0; i != allocBlocks; ++i){
		block_alloc_t* block = list.get(i);

		int nextIdx = i + 1;
		if(list.size() > nextIdx){
			block_alloc_t* nextblock = list.get(nextIdx);

			block->nextfpos = nextblock->fpos;
		}else{
			block->nextfpos = 0;
		}
	}

	for(int i = 0; i != allocBlocks; ++i){
		block_alloc_t* block = list.get(i);

		this->body->alloc(block->fpos, block->used, block->nextfpos);
	}

	handle->initOnAlloc(list.get(0)->fpos, size);
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

BlockHandle* BlockFileStore::get(uint64_t fpos) {
	BlockHandle* handle = new BlockHandle(this);

	handle->loadBlock(fpos);

	return handle;
}

void BlockFileStore::sync(bool fsync) {
	this->header->sync(fsync);
	this->body->sync(fsync);
}



} /* namespace alinous */

