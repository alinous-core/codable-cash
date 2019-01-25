

set(__src
	AbstractAddress.cpp
	AbstractTransaction.cpp
	BalanceUnit.cpp
	Base58.cpp
	BlockchainAddress.cpp
	TicketTransaction.cpp
	Transaction.cpp
	TransactionId.cpp
	TransactionInput.cpp
	TransactionInputs.cpp
	TransactionOutput.cpp
	TransactionOutputs.cpp
)
handle_sub(codablecashlib "${__src}" blockchain bc_base)

