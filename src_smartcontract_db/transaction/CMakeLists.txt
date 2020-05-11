

set(__src
	CdbTransaction.cpp
	CdbTransactionManager.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction)

