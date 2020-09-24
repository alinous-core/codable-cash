/*
 * SwapCacheFactory.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/SwapCacheFactory.h"

#include "base_io/File.h"

namespace codablecash {

SwapCacheFactory::SwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache, BtreeKeyFactory* keyFactory, AbstractBtreeDataFactory* dataFactory) {
	this->baseDir = new File(*tmpdir);
	this->diskCache = diskCache;
	this->keyFactory = keyFactory;
	this->dataFactory = dataFactory;
}

SwapCacheFactory::~SwapCacheFactory() {
	delete this->baseDir;
}

void SwapCacheFactory::resetDir() {
	this->baseDir->deleteDir();
	this->baseDir->mkdirs();

	this->diskCache = nullptr;
	this->keyFactory = nullptr;
	this->dataFactory = nullptr;
}

} /* namespace codablecash */
