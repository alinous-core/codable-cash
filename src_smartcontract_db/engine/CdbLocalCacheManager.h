/*
 * CdbLocalCacheManager.h
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#ifndef ENGINE_CDBLOCALCACHEMANAGER_H_
#define ENGINE_CDBLOCALCACHEMANAGER_H_

namespace alinous {
class File;
class DiskCacheManager;
}
using namespace alinous;

namespace codablecash {

class CdbSwapCacheFactory;
class LocalOidFactory;

class CdbLocalCacheManager {
public:
	CdbLocalCacheManager(const File* tmpdir, LocalOidFactory* localOidFacroty);
	virtual ~CdbLocalCacheManager();

private:
	File* folder;
	DiskCacheManager* diskCache;
	CdbSwapCacheFactory* cacheFactory;

	LocalOidFactory* localOidFacroty;
};

} /* namespace codablecash */

#endif /* ENGINE_CDBLOCALCACHEMANAGER_H_ */
