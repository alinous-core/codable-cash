
set(testsrc
	test_class_fw.cpp
	test_compiler_utils.cpp
	test_ctrl_statement.cpp
	test_ddl.cpp
	test_dml.cpp
	test_dom_binary.cpp
	test_exceptions.cpp
	test_exp.cpp
	test_exp_arithmetic.cpp
	test_exp_bit.cpp
	test_exp_logical.cpp
	test_main_sc.cpp
	test_parser.cpp
	test_sql_exp.cpp
	test_sql_misc.cpp
	test_statement.cpp
)
handle_sub(testall "${testsrc}" test smartcontract)

