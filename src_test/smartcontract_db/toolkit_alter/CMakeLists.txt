
set(testsrc
	TestDbSchemaAlter01.cpp
	TestDbSchemaAlter02.cpp
	TestDbSchemaAlter03.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/toolkit_alter)
