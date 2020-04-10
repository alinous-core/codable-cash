
set(testsrc
	test_do_while_stmt.cpp
	test_for_stmt.cpp
	test_if.cpp
	test_return_stmt.cpp
	test_while_stmt.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/stmt_ctrl)

