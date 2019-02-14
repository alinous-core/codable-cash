
set(testsrc
	test_class_fw.cpp
	test_ctrl_statement.cpp
	test_exp.cpp
	test_main_sc.cpp
	test_parser.cpp
)
handle_sub(testall "${testsrc}" test smartcontract)

