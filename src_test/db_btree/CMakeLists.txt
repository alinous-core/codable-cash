
set(testsrc
	test_btree.cpp
	test_cache.cpp
	test_key_format.cpp
)
handle_sub(testall "${testsrc}" test db_btree)