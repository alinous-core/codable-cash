
set(testsrc
	test_exec_alter_primary.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_alter_primary)
