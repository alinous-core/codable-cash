
set(testsrc
	test_joinpart_left.cpp
	test_joinpart_misc.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_join)
