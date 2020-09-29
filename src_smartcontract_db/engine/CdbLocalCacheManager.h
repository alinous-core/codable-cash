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
class OidKeyRecordCache;
class SingleKeyOidCache;

class CdbLocalCacheManager {
public:
	static const constexpr int DEFAULT_SWAPPINESS{1024*500};

	CdbLocalCacheManager(const File* tmpdir, LocalOidFactory* localOidFacroty);
	virtual ~CdbLocalCacheManager();

	void init();

	OidKeyRecordCache* createOidKeyRecordCache();
	SingleKeyOidCache* createSingleKeyOidCache();

private:
	File* folder;
	DiskCacheManager* diskCache;
	CdbSwapCacheFactory* cacheFactory;

	LocalOidFactory* localOidFacroty;
};

} /* namespace codablecash */

#endif /* ENGINE_CDBLOCALCACHEMANAGER_H_ */
