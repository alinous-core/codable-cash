
set(testsrc
	TestDbSchema01.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/toolkit)
