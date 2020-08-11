
set(__src
	NodeCacheRef.cpp
	NodeCache.cpp
)
handle_sub(codablecashlib "${__src}" db btree_cache)
