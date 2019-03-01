
set(testsrc
	test_class_fw.cpp
	test_ctrl_statement.cpp
	test_ddl.cpp
	test_dml.cpp
	test_exp.cpp
	test_exp_arithmetic.cpp
	test_main_sc.cpp
	test_parser.cpp
	test_sql_exp.cpp
)
handle_sub(testall "${testsrc}" test smartcontract)

