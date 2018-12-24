
set(testsrc
	test_btree.cpp
	test_cache.cpp
)
handle_sub(testall "${testsrc}" test db_btree)