
set(__src
	FeeIndex.cpp
	IndexValueFactory.cpp
	MemPool.cpp
	TransactionIdIndex.cpp
	TransactionIdKey.cpp
	TransactionIdKeyFactory.cpp
	TransactionRecord.cpp
	TransactionStore.cpp
)
handle_sub(codablecashlib "${__src}" blockchain mempool)
