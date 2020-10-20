
set(testsrc
	test_exec_alter_primary.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/ddl/table_alter_primary)
