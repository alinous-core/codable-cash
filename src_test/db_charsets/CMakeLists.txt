
set(src
	testmain.cpp
)

set(testsrc
	test_charsets.cpp
	test_charsets2.cpp
)

foreach(loop_var IN LISTS testsrc)
	list(APPEND __testsrc db_charsets/${loop_var})
endforeach()
set(db_charset_test_src ${__testsrc} PARENT_SCOPE)

#[[
set(testtarget db_charset_test)
add_executable(${testtarget} ${src} ${testsrc})
target_link_libraries(${testtarget} codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})
add_test(${testtarget} ${testtarget} -v)
]]#

set(gnodir ${CMAKE_BINARY_DIR}/src_test/CMakeFiles/testall.dir/db_charsets)
outgcov(report_test_db_charsets ${gnodir} ${testsrc})


