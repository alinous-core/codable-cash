
set(testsrc
	test_exec_alter_column_add_error.cpp
	test_exec_alter_column_drop_error.cpp
	test_exec_alter_column.cpp
	test_exec_alter_drop_column.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_alter_column)
