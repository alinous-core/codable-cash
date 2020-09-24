
set(testsrc
	test_oid_cache.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/cache)
