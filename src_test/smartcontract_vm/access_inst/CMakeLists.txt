
set(testsrc
	test_array_access.cpp
	test_array_instruction_access.cpp
	test_expression_access.cpp
	test_misc.cpp
	test_nullpointerexception.cpp
	test_static_method_access.cpp
	test_static_variable_access.cpp
	test_superclass_method_access.cpp
	test_this_access.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/access_inst)

