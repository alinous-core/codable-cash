

set(__src
	AbstractDatabaseLock.cpp
	AbstractLockHandle.cpp
	DatabaseLevelLock.cpp
	ReadLock.cpp
	WriteLock.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db engine_lock)

