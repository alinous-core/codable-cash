
set(testsrc
	test_alter_log_binary.cpp
	test_alter_modify_log_binary.cpp
	test_alter_parse.cpp
	test_alter_parse_modify.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/table_alter)
