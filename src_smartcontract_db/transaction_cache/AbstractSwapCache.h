/*
 * AbstractSwapCache.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_
#define TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_
#include <cstdint>

namespace alinous {
class File;
class DiskCacheManager;
class BtreeKeyFactory;
class AbstractBtreeDataFactory;
class UnicodeString;
class IBlockObject;
class AbstractBtreeKey;
class Btree;
class BtreeOnMemory;
class BtreeConfig;
}
using namespace alinous;

namespace codablecash {

class AbstractSwapCache {
public:
	AbstractSwapCache(const File* folder, const UnicodeString* name, BtreeKeyFactory* keyFactory, AbstractBtreeDataFactory* dataFactory, DiskCacheManager* diskCache);
	virtual ~AbstractSwapCache();

	void setSwappiness(int swappiness) {
		this->swappiness = swappiness;
	}

	void init(uint64_t nodeNumber);
	void removeFiles() noexcept;

protected:
	void swapIfNecessary();

	void putData(const AbstractBtreeKey* key, const IBlockObject* data);
	const IBlockObject* findData(const AbstractBtreeKey* key);

private:
	void swapToDisk();
	void putDataIntoMemory(const AbstractBtreeKey* key, const IBlockObject* data);
	void putDataIntoDisk(const AbstractBtreeKey* key, const IBlockObject* data);
	const IBlockObject* findDataFromMemory(const AbstractBtreeKey* key);
	const IBlockObject* findDataFromDisk(const AbstractBtreeKey* key);

	void setCurrent(IBlockObject* obj) noexcept;

protected:
	File* folder;
	UnicodeString* name;
	BtreeKeyFactory* keyFactory;
	AbstractBtreeDataFactory* dataFactory;
	DiskCacheManager* diskCache;

	uint64_t currentSize;
	int swappiness;

	bool useDisk;

	Btree* btree;
	BtreeOnMemory* memoryBtree;

	IBlockObject* current;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_ */
