
set(__src
	MemPool.cpp
	TransactionRecord.cpp
)
handle_sub(codablecashlib "${__src}" blockchain mempool)
