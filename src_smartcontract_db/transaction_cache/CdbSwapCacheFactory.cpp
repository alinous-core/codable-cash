/*
 * CdbSwapCacheFactory.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/CdbSwapCacheFactory.h"

#include "table_record/CdbDataFactory.h"
#include "table_record/CdbKeyFactory.h"

namespace codablecash {

CdbSwapCacheFactory::CdbSwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache)
		: SwapCacheFactory(tmpdir, diskCache, nullptr, nullptr) {
	this->dataFactory = new CdbDataFactory();
	this->keyFactory = new CdbKeyFactory();
}

CdbSwapCacheFactory::~CdbSwapCacheFactory() {
	delete this->dataFactory;
	delete this->keyFactory;
}

} /* namespace codablecash */
