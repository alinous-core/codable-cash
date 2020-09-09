
set(testsrc
	test_alter_parse.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_alter)
