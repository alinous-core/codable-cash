
set(testsrc
	test_if.cpp
	test_return_stmt.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/stmt_ctrl)

