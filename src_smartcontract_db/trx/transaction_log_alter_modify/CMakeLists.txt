

set(__src
	AlterAddPrimaryKeyCommandLog.cpp
	AlterDropPrimaryKeyCommandLog.cpp
	AlterModifyCommandLog.cpp
	AlterRenameColumnCommandLog.cpp
	AlterRenameTableCommandLog.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db trx/transaction_log_alter_modify)

