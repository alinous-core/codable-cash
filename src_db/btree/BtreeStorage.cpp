/*
 * BtreeStorage.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/BtreeStorage.h"
#include "base_io/File.h"
#include "filestore_block/BlockFileStore.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

namespace alinous {

BtreeStorage::BtreeStorage(File* folder, UnicodeString* name) {
	this->name = name;
	this->folder = folder;
	this->store = nullptr;
}

BtreeStorage::~BtreeStorage() {
	this->name = nullptr;
	this->folder = nullptr;
	if(this->store != nullptr){
		delete this->store, this->store = nullptr;
	}
}

void BtreeStorage::create(DiskCacheManager* cacheManager, BtreeConfig* config) {
	UnicodeString* folderstr = this->folder->getAbsolutePath();
	StackRelease<UnicodeString> __st_folderstr(folderstr);

	BlockFileStore* blockstore = new BlockFileStore(folderstr, this->name, cacheManager);
	StackRelease<BlockFileStore> __st_blockstore(blockstore);

	blockstore->createStore(true, 256, 256);

	blockstore->open(false);



	blockstore->close();
}

} /* namespace alinous */
