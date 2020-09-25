
set(testsrc
	test_local_oid.cpp
	test_oid_cache.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/cache)
