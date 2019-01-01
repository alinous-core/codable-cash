
set(testsrc
	test_address.cpp
	test_base58.cpp
	test_blockchain_fw.cpp
	test_shard_stat.cpp
)
handle_sub(testall "${testsrc}" test blockchain)

