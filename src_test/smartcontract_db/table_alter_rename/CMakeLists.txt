
set(testsrc
	test_exec_alter_rename_table_err.cpp
	test_exec_alter_rename_table.cpp
	test_exec_later_rename_column.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_alter_rename)
