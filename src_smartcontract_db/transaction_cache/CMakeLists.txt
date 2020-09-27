

set(__src
	AbstractSwapCache.cpp
	CdbSwapCacheFactory.cpp
	SingleKeyOidCache.cpp
	SwapCacheFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_cache)

