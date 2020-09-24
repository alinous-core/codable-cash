

set(__src
	AbstractSwapCache.cpp
	SingleKeyOidCache.cpp
	SwapCacheFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_cache)

