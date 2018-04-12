
set(src
	"testmain.cpp"
)

set(cryptotestsrc
	test_mpz.cpp
	test_yescript.cpp
	test_schnorr.cpp
)

add_executable(testmain ${src} ${cryptotestsrc})
target_link_libraries(testmain codablelib extlib gmp ${CPPUTEST_LDFLAGS})

add_test(testcrypto testmain -v)



