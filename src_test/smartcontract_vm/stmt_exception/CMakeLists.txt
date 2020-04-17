
set(testsrc
	test_try_catch_err.cpp
	test_try_catch.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/stmt_exception)

