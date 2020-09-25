/*
 * SwapCacheFactory.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_SWAPCACHEFACTORY_H_
#define TRANSACTION_CACHE_SWAPCACHEFACTORY_H_

#include <cstdint>

namespace alinous {
class File;
class DiskCacheManager;
class BtreeKeyFactory;
class AbstractBtreeDataFactory;
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class SwapCacheFactory {
public:
	SwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache, BtreeKeyFactory* keyFactory, AbstractBtreeDataFactory* dataFactory);
	virtual ~SwapCacheFactory();

	void resetDir();

	virtual UnicodeString* getName() noexcept = 0;

protected:
	File* baseDir;
	DiskCacheManager* diskCache;
	BtreeKeyFactory* keyFactory;
	AbstractBtreeDataFactory* dataFactory;

	uint64_t serial;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_SWAPCACHEFACTORY_H_ */
