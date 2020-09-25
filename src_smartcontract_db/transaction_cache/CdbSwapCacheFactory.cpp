/*
 * CdbSwapCacheFactory.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/CdbSwapCacheFactory.h"

#include "table_record/CdbDataFactory.h"
#include "table_record/CdbKeyFactory.h"

#include "base/UnicodeString.h"

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

SingleKeyOidCache* CdbSwapCacheFactory::createSingleKeyOidCache() {

}

} /* namespace codablecash */
