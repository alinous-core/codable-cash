
set(testsrc
	test_array_access.cpp
	test_array_instruction_access.cpp
	test_expression_access.cpp
	test_misc.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/access_inst)

