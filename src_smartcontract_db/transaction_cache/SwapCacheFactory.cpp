/*
 * SwapCacheFactory.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/SwapCacheFactory.h"

#include "base_io/File.h"

namespace codablecash {

SwapCacheFactory::SwapCacheFactory(const File* tmpdir) {
	this->baseDir = new File(*tmpdir);
}

SwapCacheFactory::~SwapCacheFactory() {
	delete this->baseDir;
}

void SwapCacheFactory::resetDir() {
	this->baseDir->deleteDir();
	this->baseDir->mkdirs();
}

} /* namespace codablecash */
