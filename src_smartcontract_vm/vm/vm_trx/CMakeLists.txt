

set(__src
	StackTransactionReset.cpp
	VmTransactionHandler.cpp
	VmTransactionHandlerException.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm vm/vm_trx)

