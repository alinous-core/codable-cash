
set(testsrc
	test_thread.cpp
	TestCountRunner.cpp
)
handle_sub(testall "${testsrc}" test db_base_thread)

