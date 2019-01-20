
set(testsrc
	test_charsets.cpp
	test_charsets2.cpp
)
handle_sub(testall "${testsrc}" test db/db_charsets)

