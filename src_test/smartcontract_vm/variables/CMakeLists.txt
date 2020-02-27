
set(testsrc
	test_allocation.cpp
	test_array_variables.cpp
	test_init_class.cpp
	test_local_variavle.cpp
	test_string_variables.cpp
	test_type_checker.cpp
	test_variables.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/variables)

