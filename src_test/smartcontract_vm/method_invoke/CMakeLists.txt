
set(testsrc
	test_call_maininst.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/method_invoke)

