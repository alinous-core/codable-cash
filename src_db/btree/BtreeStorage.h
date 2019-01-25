/*
 * BtreeStorage.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_BTREESTORAGE_H_
#define BTREE_BTREESTORAGE_H_

#include <cstdint>

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
class IBlockObject;

class BtreeKeyFactory;
class AbstractBtreeDataFactory;


class BtreeStorage {
public:
	BtreeStorage(File* folder, UnicodeString* name, BtreeKeyFactory* factory, AbstractBtreeDataFactory* dfactory);
	virtual ~BtreeStorage();

	bool exists() const noexcept;
	void create(DiskCacheManager* cacheManager, BtreeConfig* config);

	void open(int numDataBuffer, int numNodeBuffer, DiskCacheManager* cacheManager);
	void close();
	void sync(bool syncDisk);

	BtreeHeaderBlock* loadHeader();
	NodeHandle* loadRoot();
	NodeHandle* loadNode(uint64_t fpos);
	IBlockObject* loadData(uint64_t fpos);

	void remove(uint64_t fpos);

	void setRootFpos(uint64_t rootFpos);

	uint64_t storeData(const IBlockObject* data);
	uint64_t storeData(const IBlockObject* data, uint64_t fpos);
	void removeData(uint64_t dataFpos);

	uint64_t storeNode(AbstractTreeNode* node);
	void updateNode(AbstractTreeNode* node);

	void updateRootFpos(uint64_t rootFpos);

	const AbstractBtreeDataFactory* getDataFactory() const noexcept;

private:
	BtreeHeaderBlock* makeHeader(BtreeConfig* config, uint64_t rootFpos);
	static AbstractTreeNode* makeNodeFromBinary(ByteBuffer* buff, BtreeKeyFactory* factory);

private:
	UnicodeString* name;
	File* folder;
	BtreeKeyFactory* factory;
	AbstractBtreeDataFactory* dfactory;

	BlockFileStore* store;
	NodeCache* cache;

	uint64_t rootFpos;

	SynchronizedLock lock;
};

} /* namespace alinous */

#endif /* BTREE_BTREESTORAGE_H_ */
