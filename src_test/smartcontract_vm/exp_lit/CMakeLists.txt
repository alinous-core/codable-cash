
set(testsrc
	test_bool.cpp
	test_null.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/exp_lit)

