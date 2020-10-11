
set(testsrc
	TestDbSchemaAlter01.cpp
	TestDbSchemaAlter02.cpp
	TestDbSchemaAlter03.cpp
	TestDbSchemaAlter04.cpp
	TestDbSchemaAlterModifyIndexCheck.cpp
	TestDbSchemaAlterText01.cpp
	TestDbSchemaAlterTextUnique01.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/toolkit_alter)
