/*
 * SwapCacheFactory.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_SWAPCACHEFACTORY_H_
#define TRANSACTION_CACHE_SWAPCACHEFACTORY_H_

namespace alinous {
class File;
class DiskCacheManager;
class BtreeKeyFactory;
class AbstractBtreeDataFactory;
}
using namespace alinous;

namespace codablecash {

class SwapCacheFactory {
public:
	SwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache, BtreeKeyFactory* keyFactory, AbstractBtreeDataFactory* dataFactory);
	virtual ~SwapCacheFactory();

	void resetDir();


protected:
	File* baseDir;
	DiskCacheManager* diskCache;
	BtreeKeyFactory* keyFactory;
	AbstractBtreeDataFactory* dataFactory;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_SWAPCACHEFACTORY_H_ */
