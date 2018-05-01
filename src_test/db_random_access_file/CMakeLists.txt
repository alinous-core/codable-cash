
set(testsrc
	test_random_access_file.cpp
	test_thread_random_access_file.cpp
)
handle_sub(testall "${testsrc}" test db_random_access_file)

