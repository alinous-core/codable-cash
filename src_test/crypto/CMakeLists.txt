
set(testsrc
	test_mpz.cpp
	test_yescript.cpp
	test_schnorr.cpp
)

foreach(loop_var IN LISTS testsrc)
	list(APPEND __testsrc crypto/${loop_var})
endforeach()
set(cryptotestsrc ${__testsrc} PARENT_SCOPE)

#[[
add_executable(testcrypt ${src} ${testsrc})
target_link_libraries(testcrypt codablelib extlib gmp ${CPPUTEST_LDFLAGS})
#add_test(testcrypto testmain -v)
]]#


set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_test/crypto)
outgcov(report_test_crypto ${gnodir} "${testsrc}")
