
set(testsrc
	TestSetup.cpp
)
set_parentv("${testsrc}" test_utils test_utils_test_src)


set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_test/test_utils)
outgcov(report_test_utils ${gnodir} "${testsrc}")


