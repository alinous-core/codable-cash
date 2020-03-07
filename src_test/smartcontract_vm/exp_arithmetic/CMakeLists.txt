
set(testsrc
	test_add.cpp
	test_mul.cpp
	test_negate.cpp
	test_post_inc.cpp
	test_pre_inc.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/exp_arithmetic)

