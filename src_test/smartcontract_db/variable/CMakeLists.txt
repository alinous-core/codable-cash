
set(testsrc
	test_dom_base.cpp
	test_vm_hash.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/variable)
