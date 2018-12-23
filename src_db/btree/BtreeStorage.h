/*
 * BtreeStorage.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_BTREESTORAGE_H_
#define BTREE_BTREESTORAGE_H_

#include <inttypes.h>

namespace alinous {

class UnicodeString;
class File;
class BlockFileStore;
class DiskCacheManager;
class BtreeConfig;
class BtreeHeaderBlock;
class NodeCache;

class BtreeStorage {
public:
	BtreeStorage(File* folder, UnicodeString* name);
	virtual ~BtreeStorage();

	void create(DiskCacheManager* cacheManager, BtreeConfig* config);

	void open(int numDataBuffer, int numNodeBuffer);
	void close();

private:
	BtreeHeaderBlock* makeHeader(BtreeConfig* config, uint64_t rootFpos);

private:
	UnicodeString* name;
	File* folder;
	BlockFileStore* store;
	NodeCache* cache;
};

} /* namespace alinous */

#endif /* BTREE_BTREESTORAGE_H_ */
