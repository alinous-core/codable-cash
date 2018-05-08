
set(__src
	Check.cpp
	ErrorOccurrence.cpp
	ErrorPointManager.cpp
	TestCase.cpp
	TestExecutor.cpp
	TestGroup.cpp
	TestGroupActions.cpp
)
handle_sub(codablecashlib "${__src}" db debug)
