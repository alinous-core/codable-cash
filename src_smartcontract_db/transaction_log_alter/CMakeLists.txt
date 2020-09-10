

set(__src
	AlterAddColumnCommandLog.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_log_alter)

