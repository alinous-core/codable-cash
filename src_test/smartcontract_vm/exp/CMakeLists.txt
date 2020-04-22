
set(testsrc
	test_cast_exp.cpp
	test_parenthesis_exp.cpp
	test_variable_id.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/exp)

