
set(testsrc
	test_bit_and.cpp
	test_bit_or.cpp
	test_bit_reverse.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_vm/exp_bit)

