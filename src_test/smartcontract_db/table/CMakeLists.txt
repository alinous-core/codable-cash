
set(testsrc
	test_create_table.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table)
