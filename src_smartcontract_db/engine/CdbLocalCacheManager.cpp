/*
 * CdbLocalCacheManager.cpp
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#include "engine/CdbLocalCacheManager.h"

#include "base_io/File.h"

#include "random_access_file/DiskCacheManager.h"

#include "transaction_cache/CdbSwapCacheFactory.h"

#include "base/StackRelease.h"

namespace codablecash {

CdbLocalCacheManager::CdbLocalCacheManager(const File* tmpdir, LocalOidFactory* localOidFacroty) {
	this->folder = new File(*tmpdir);
	this->diskCache = new DiskCacheManager();

	File* cacheDir = this->folder->get(L"swap"); __STP(cacheDir);

	this->cacheFactory = new CdbSwapCacheFactory(cacheDir, this->diskCache);

	this->localOidFacroty = localOidFacroty;
}

CdbLocalCacheManager::~CdbLocalCacheManager() {
	delete this->folder;
	delete this->diskCache;
	delete this->cacheFactory;

	this->localOidFacroty = nullptr;
}

} /* namespace codablecash */
