/*
 * BtreeStorage.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_BTREESTORAGE_H_
#define BTREE_BTREESTORAGE_H_

#include <inttypes.h>

#include "base_thread/SynchronizedLock.h"

namespace alinous {

class UnicodeString;
class File;
class BlockFileStore;
class DiskCacheManager;
class BtreeConfig;
class BtreeHeaderBlock;
class NodeCache;
class NodeHandle;
class AbstractTreeNode;
class ByteBuffer;

class BTreeKeyFactory;

class BtreeStorage {
public:
	BtreeStorage(File* folder, UnicodeString* name, BTreeKeyFactory* factory);
	virtual ~BtreeStorage();

	void create(DiskCacheManager* cacheManager, BtreeConfig* config);

	void open(int numDataBuffer, int numNodeBuffer, DiskCacheManager* cacheManager);
	void close();

	BtreeHeaderBlock* loadHeader();
	NodeHandle* loadRoot();
	NodeHandle* loadNode(uint64_t fpos);


	void setRootFpos(uint64_t rootFpos){
		this->rootFpos = rootFpos;
	}


private:
	BtreeHeaderBlock* makeHeader(BtreeConfig* config, uint64_t rootFpos);
	static AbstractTreeNode* makeNodeFromBinary(ByteBuffer* buff, BTreeKeyFactory* factory);

private:
	UnicodeString* name;
	File* folder;
	BTreeKeyFactory* factory;

	BlockFileStore* store;
	NodeCache* cache;

	uint64_t rootFpos;

	SynchronizedLock lock;
};

} /* namespace alinous */

#endif /* BTREE_BTREESTORAGE_H_ */
