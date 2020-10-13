/*
 * CdbSwapCacheFactory.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_CDBSWAPCACHEFACTORY_H_
#define TRANSACTION_CACHE_CDBSWAPCACHEFACTORY_H_

#include "trx/transaction_cache/SwapCacheFactory.h"

namespace codablecash {

class CdbKeyFactory;
class CdbDataFactory;
class SingleKeyOidCache;
class OidKeyRecordCache;

class CdbSwapCacheFactory: public SwapCacheFactory {
public:
	static const UnicodeString PREFIX_SINGLE_KEY;

	CdbSwapCacheFactory(const File* tmpdir, DiskCacheManager* diskCache);
	virtual ~CdbSwapCacheFactory();

	virtual UnicodeString* getName() noexcept;

	SingleKeyOidCache* createSingleKeyOidCache(int swappiness);
	OidKeyRecordCache* createOidKeyRecordCache(int swappiness);

};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_CDBSWAPCACHEFACTORY_H_ */
