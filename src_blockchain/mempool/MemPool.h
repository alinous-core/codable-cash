/*
 * MemPool.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_MEMPOOL_H_
#define MEMPOOL_MEMPOOL_H_



namespace alinous {
class File;
class Btree;
class DiskCacheManager;
class BTreeKeyFactory;
}

namespace codablecash {
using namespace alinous;

class MemPool {
public:
	MemPool(File* file);
	virtual ~MemPool();

	void init();
	void close();

private:
	File* file;
	DiskCacheManager* cacheManager;
	BTreeKeyFactory* keyFactory;
	Btree* mainStore;
};

} /* namespace codablecash */

#endif /* MEMPOOL_MEMPOOL_H_ */
