/*
 * SwapCacheFactory.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "trx/transaction_cache/SwapCacheFactory.h"

#include "base_io/File.h"

namespace codablecash {

SwapCacheFactory::SwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache, BtreeKeyFactory* keyFactory, AbstractBtreeDataFactory* dataFactory) {
	this->baseDir = new File(*tmpdir);
	this->diskCache = diskCache;
	this->keyFactory = keyFactory;
	this->dataFactory = dataFactory;

	this->serial = 0;
}

SwapCacheFactory::~SwapCacheFactory() {
	delete this->baseDir;

	this->diskCache = nullptr;
	this->keyFactory = nullptr;
	this->dataFactory = nullptr;
}

void SwapCacheFactory::resetDir() {
	this->baseDir->deleteDir();
	this->baseDir->mkdirs();
}

} /* namespace codablecash */
