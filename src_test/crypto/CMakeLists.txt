
set(testsrc
	test_mpz.cpp
	test_yescript.cpp
	test_schnorr.cpp
)
handle_sub("${testsrc}" test crypto)

