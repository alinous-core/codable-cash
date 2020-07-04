
set(testsrc
	test_array_compare.cpp
	test_array_instance.cpp
	test_class_compare.cpp
	test_class_object.cpp
	test_exception_inst.cpp
	test_misc_compare.cpp
	test_numeric_ref.cpp
	test_primitive_compare.cpp
	test_primitive.cpp
	test_ref_factory.cpp
	test_root_obj.cpp
	test_vm_stack.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/instance)

