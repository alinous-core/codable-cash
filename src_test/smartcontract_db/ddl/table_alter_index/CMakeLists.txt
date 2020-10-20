
set(testsrc
	test_exec_alter_index_add_err.cpp
	test_exec_alter_index_drop_err.cpp
	test_exec_alter_index.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/ddl/table_alter_index)
