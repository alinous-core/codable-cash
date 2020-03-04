
set(testsrc
	test_analyzed_class.cpp
	test_analyzed_context.cpp
	test_analyzed_type.cpp
	test_class_instance.cpp
	test_ext_objects.cpp
	test_interface.cpp
	test_exec_fw.cpp
	test_main_vm.cpp
	test_sc_declare_types.cpp
	test_type_resolver.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/base)

