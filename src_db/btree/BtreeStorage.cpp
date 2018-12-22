/*
 * BtreeStorage.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/BtreeStorage.h"
#include "btree/BtreeHeaderBlock.h"

#include "base_io/File.h"
#include "base_io/ReverseByteBuffer.h"
#include "filestore_block/BlockFileStore.h"
#include "filestore_block/BlockHandle.h"

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

	BtreeHeaderBlock* header = makeHeader(config, 0);
	StackRelease<BtreeHeaderBlock> __st_header(header);

	int headerSize = header->binarySize();
	ByteBuffer* buff = ReverseByteBuffer::allocate(headerSize);
	StackRelease<ByteBuffer> __st_buff(buff);

	header->toBinary(buff);
	buff->position(0);


	BlockHandle* handle = blockstore->alloc(headerSize);
	StackRelease<BlockHandle> __st_handle(handle);

	handle->write((const char*)buff->array(), headerSize);


	blockstore->close();
}

BtreeHeaderBlock* BtreeStorage::makeHeader(BtreeConfig* config, uint64_t rootFpos) {
	BtreeHeaderBlock* header = new BtreeHeaderBlock();
	header->setConfig(config);
	header->setRootFpos(rootFpos);

	return header;

}

} /* namespace alinous */
