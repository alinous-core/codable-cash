
set(testsrc
	test_btree.cpp
)
handle_sub(testall "${testsrc}" test db_btree)