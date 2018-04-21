
set(testsrc
	test_mpz.cpp
	test_yescript.cpp
	test_schnorr.cpp
)
handle_sub(testall "${testsrc}" test crypto)

