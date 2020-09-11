

set(__src
	AbstractDatabaseLock.cpp
	DatabaseLevelLock.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db engine_lock)

