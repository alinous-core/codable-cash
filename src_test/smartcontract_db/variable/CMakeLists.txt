
set(testsrc
	test_dom_base.cpp
	test_vm_bitset.cpp
	test_vm_hash.cpp
	test_vm_mem_list_sort.cpp
)
handle_sub(testall "${testsrc}" test smartcontract_db/variable)
