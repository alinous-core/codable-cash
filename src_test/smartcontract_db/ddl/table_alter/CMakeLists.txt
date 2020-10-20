
set(testsrc
	test_alter_log_binary.cpp
	test_alter_parse.cpp
	test_exec_alter_misc.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/ddl/table_alter)
