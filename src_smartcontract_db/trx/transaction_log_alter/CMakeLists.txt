

set(__src
	AbstractAlterCommandLog.cpp
	AlterAddColumnCommandLog.cpp
	AlterAddIndexCommandLog.cpp
	AlterDropColumnCommandLog.cpp
	AlterDropIndexCommandLog.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db trx/transaction_log_alter)

