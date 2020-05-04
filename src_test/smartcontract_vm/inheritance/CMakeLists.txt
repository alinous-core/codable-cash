
set(testsrc
	test_inheritance.cpp
	test_super_constructor.cpp
	test_super_variables.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/inheritance)

