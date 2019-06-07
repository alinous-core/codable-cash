
set(testsrc
	test_class_instance.cpp
	test_main_vm.cpp
	test_memory_manager.cpp
	test_vm_malloc.cpp
	test_vmemlist.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm)

