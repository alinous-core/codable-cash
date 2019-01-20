
set(testsrc
	CriticalSectionMarker.cpp
	CriticalSectionMarkerException.cpp
	GateTester.cpp
	test_concurrent_gate.cpp
	test_thread.cpp
	TestCountRunner.cpp
)
handle_sub(testall "${testsrc}" test db/db_base_thread)

