
set(testsrc
	DummyAddress.cpp
	DummyTrxUtils.cpp
	test_address.cpp
	test_base58.cpp
	test_blockchain_fw.cpp
	test_mempool.cpp
	test_shard_stat.cpp
	test_transaction.cpp
)
handle_sub(testall "${testsrc}" test blockchain)

