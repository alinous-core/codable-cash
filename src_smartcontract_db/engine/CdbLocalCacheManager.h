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

class CdbLocalCacheManager {
public:
	explicit CdbLocalCacheManager(const File* tmpdir);
	virtual ~CdbLocalCacheManager();

private:
	File* folder;
	DiskCacheManager* diskCache;
	CdbSwapCacheFactory* cacheFactory;
};

} /* namespace codablecash */

#endif /* ENGINE_CDBLOCALCACHEMANAGER_H_ */
