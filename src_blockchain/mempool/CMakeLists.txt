
set(__src
	FeeIndex.cpp
	IndexValueFactory.cpp
	MemPool.cpp
	TransactionIdIndex.cpp
	TransactionRecord.cpp
	TransactionStore.cpp
)
handle_sub(codablecashlib "${__src}" blockchain mempool)
