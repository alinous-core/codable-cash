
add_subdirectory(crypto)
add_subdirectory(db_base)
add_subdirectory(db_base_io)
add_subdirectory(db_charsets)


set(testsrc ${cryptotestsrc} ${db_base_test_src} ${db_base_io_test_src} ${db_charset_test_src})

message (STATUS "test source codes ${testsrc}")

set(testtarget testall)

add_executable(${testtarget} testallmain.cpp ${testsrc})
target_link_libraries(${testtarget} codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

add_test(${testtarget} ${testtarget} -v)

