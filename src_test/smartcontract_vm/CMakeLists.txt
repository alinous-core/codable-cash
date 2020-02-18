
set(testsrc
	test_class_instance.cpp
	test_exec_fw.cpp
	test_ext_objects.cpp
	test_main_vm.cpp
	test_vm_malloc.cpp
	test_vmemlist.cpp
	VmTestUtils.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm)

