
set(testsrc
	TempValue.cpp
	test_btree.cpp
	test_cache.cpp
	test_key_format.cpp
)
handle_sub(testall "${testsrc}" test db/db_btree)