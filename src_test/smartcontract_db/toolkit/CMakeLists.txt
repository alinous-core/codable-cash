
set(testsrc
	TestDbSchema01.cpp
	TestDbSchemaBase.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/toolkit)
