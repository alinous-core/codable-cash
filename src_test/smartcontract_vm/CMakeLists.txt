
set(testsrc
	test_class_instance.cpp
	test_main_vm.cpp
	test_memory_manager.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm)

