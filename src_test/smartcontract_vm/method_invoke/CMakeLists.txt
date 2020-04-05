
set(testsrc
	test_call_maininst.cpp
	test_function_call_arg.cpp
	test_function_call.cpp
	test_virtual_func_call.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/method_invoke)

