/*
 * CdbSwapCacheFactory.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/CdbSwapCacheFactory.h"
#include "transaction_cache/SingleKeyOidCache.h"

#include "table_record/CdbDataFactory.h"
#include "table_record/CdbKeyFactory.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"


namespace codablecash {

const UnicodeString CdbSwapCacheFactory::PREFIX_SINGLE_KEY(L"singlekey_");

CdbSwapCacheFactory::CdbSwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache)
		: SwapCacheFactory(tmpdir, diskCache, nullptr, nullptr) {
	this->dataFactory = new CdbDataFactory();
	this->keyFactory = new CdbKeyFactory();
}

CdbSwapCacheFactory::~CdbSwapCacheFactory() {
	delete this->dataFactory;
	delete this->keyFactory;
}

UnicodeString* CdbSwapCacheFactory::getName() noexcept {
	UnicodeString* name = new UnicodeString(CdbSwapCacheFactory::PREFIX_SINGLE_KEY);

	name->append((int)this->serial++);

	return name;
}

SingleKeyOidCache* CdbSwapCacheFactory::createSingleKeyOidCache(int swappiness) {
	UnicodeString* name = getName(); __STP(name);

	SingleKeyOidCache* cache = new SingleKeyOidCache(name, dynamic_cast<CdbKeyFactory*>(this->keyFactory),
			dynamic_cast<CdbDataFactory*>(this->dataFactory), this->diskCache);
	cache->setSwappiness(swappiness);
	cache->init();

	return cache;
}

} /* namespace codablecash */
