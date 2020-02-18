
set(testsrc
	test_gc.cpp
	test_memory_manager.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/memory)

