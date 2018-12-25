/*
 * BtreeStorage.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/BtreeStorage.h"
#include "btree/BtreeHeaderBlock.h"
#include "btree/InfinityKey.h"
#include "btree/TreeNode.h"
#include "btree/BtreeConfig.h"
#include "btree/NodeCache.h"

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
	this->cache = nullptr;
	this->rootFpos = 0;
}

BtreeStorage::~BtreeStorage() {
	this->name = nullptr;
	this->folder = nullptr;
	if(this->store != nullptr){
		delete this->store, this->store = nullptr;
	}
	if(this->cache != nullptr){
		delete this->cache, this->cache = nullptr;
	}
}

void BtreeStorage::create(DiskCacheManager* cacheManager, BtreeConfig* config) {
	UnicodeString* folderstr = this->folder->getAbsolutePath();
	StackRelease<UnicodeString> __st_folderstr(folderstr);

	BlockFileStore* blockstore = new BlockFileStore(folderstr, this->name, cacheManager);
	StackRelease<BlockFileStore> __st_blockstore(blockstore);

	blockstore->createStore(true, 256, 256);

	blockstore->open(false);

	uint64_t rootFpos;
	{
		// pre alloc
		BlockHandle* handle = blockstore->alloc(1);
		delete handle;

		handle = blockstore->alloc(1);

		rootFpos = handle->getFpos();
		delete handle;
	}

	// root node
	{
		BlockHandle* handle = blockstore->get(rootFpos);
		StackRelease<BlockHandle> __st_handle(handle);

		InfinityKey* infinityKey = new InfinityKey();
		TreeNode rootNode(true, config->nodeNumber, infinityKey, true);

		int cap = rootNode.binarySize();
		ByteBuffer* buff = ReverseByteBuffer::allocateWithEndian(cap, true);
		StackRelease<ByteBuffer> __st_buff(buff);

		rootNode.toBinary(buff);

		handle->write((const char*)buff->array(), cap);
	}

	{
		// first header
		BtreeHeaderBlock* header = makeHeader(config, rootFpos);
		StackRelease<BtreeHeaderBlock> __st_header(header);


		int headerSize = header->binarySize();
		ByteBuffer* buff = ReverseByteBuffer::allocateWithEndian(headerSize, true);
		StackRelease<ByteBuffer> __st_buff(buff);

		header->toBinary(buff);
		buff->position(0);

		BlockHandle* handle = blockstore->get(0);
		StackRelease<BlockHandle> __st_handle(handle);

		handle->write((const char*)buff->array(), headerSize);
	}

	blockstore->close();
}



BtreeHeaderBlock* BtreeStorage::makeHeader(BtreeConfig* config, uint64_t rootFpos) {
	BtreeHeaderBlock* header = new BtreeHeaderBlock();
	header->setConfig(config);
	header->setRootFpos(rootFpos);

	return header;

}

void BtreeStorage::open(int numDataBuffer, int numNodeBuffer, DiskCacheManager* cacheManager) {
	UnicodeString* folderstr = this->folder->getAbsolutePath();
	StackRelease<UnicodeString> __st_folderstr(folderstr);

	this->store = new BlockFileStore(folderstr, this->name, cacheManager);
	this->store->open(false);

	this->cache = new NodeCache(numDataBuffer, numNodeBuffer);
}

BtreeHeaderBlock* BtreeStorage::loadHeader() {
	// load 0 fpos
	BlockHandle* handle = this->store->get(0);
	StackRelease<BlockHandle> __st_handle(handle);

	ByteBuffer* buff = handle->getBuffer();
	buff->position(0);

	BtreeHeaderBlock* header = BtreeHeaderBlock::fromBinary(buff);
	return header;
}

void BtreeStorage::close() {
	this->store->close();
	this->cache->clear();
}


} /* namespace alinous */

