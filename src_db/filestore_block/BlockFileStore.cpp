/*
 * BlockFileStore.cpp
 *
 *  Created on: 2018/10/06
 *      Author: iizuka
 */

#include "filestore_block/BlockFileStore.h"

#include "filestore_block/BlockFileHeader.h"
#include "filestore_block/BlockFileBody.h"

namespace alinous {

BlockFileStore::BlockFileStore(UnicodeString* dir, UnicodeString* name, DiskCacheManager* cacheManager) noexcept
	: FileStore(dir, name, cacheManager)
{
	this->header = nullptr;
	this->body = nullptr;
}

BlockFileStore::~BlockFileStore() noexcept {
	if(this->header){
		delete this->header;
	}
	if(this->body){
		delete this->body;
	}
}

void BlockFileStore::createStore(bool del, uint64_t defaultSize) noexcept(false) {
	FileStore::createStore(del, defaultSize);

}


bool BlockFileStore::isOpened() const noexcept {
	return FileStore::isOpened();
}

void BlockFileStore::close() noexcept {

	FileStore::close();
}

} /* namespace alinous */

