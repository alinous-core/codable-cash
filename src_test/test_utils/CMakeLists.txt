
set(testsrc
	Check.cpp
	TestBreak.cpp
	TestSetup.cpp
	TestCase.cpp
	TestEnv.cpp
	TestExecutor.cpp
	TestGroup.cpp
	TestGroupActions.cpp
	TestParams.cpp
)
handle_sub(testall "${testsrc}" test test_utils)


