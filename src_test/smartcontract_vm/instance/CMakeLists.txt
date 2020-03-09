
set(testsrc
	test_array_compare.cpp
	test_class_compare.cpp
	test_misc_compare.cpp
	test_numeric_ref.cpp
	test_ref_factory.cpp
	test_vm_stack.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/instance)

