
set(testsrc
	test_equality_exp.cpp
	test_logical_and.cpp
	test_logical_or.cpp
	test_not_exp.cpp
	test_relational_exp.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/exp_logical)

