

set(__src
	AlterAddColumnCommandLog.cpp
	AlterAddIndexCommandLog.cpp
	AlterDropColumnCommandLog.cpp
	AlterDropIndexCommandLog.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db transaction_log_alter)

