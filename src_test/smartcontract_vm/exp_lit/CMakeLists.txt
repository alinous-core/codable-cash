
set(testsrc
	test_bool.cpp
	test_null.cpp
	test_string_literal.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/exp_lit)

