
set(testsrc
	test_charsets.cpp
	test_charsets2.cpp
)
set_parentv("${testsrc}" db_charsets db_charset_test_src)


set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_test/db_charsets)
outgcov(report_test_db_charsets ${gnodir} "${testsrc}")


