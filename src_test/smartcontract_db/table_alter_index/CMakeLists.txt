
set(testsrc
	test_exec_alter_index_add_err.cpp
	test_exec_alter_index.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_alter_index)
