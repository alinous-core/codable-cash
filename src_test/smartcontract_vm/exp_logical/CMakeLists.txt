
set(testsrc
	test_equality_exp.cpp
	test_not_exp.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/exp_logical)

