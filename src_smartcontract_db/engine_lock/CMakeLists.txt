

set(__src
	AbstractDatabaseLock.cpp
	AbstractLockHandle.cpp
	DatabaseLevelLock.cpp
	ReadLockHandle.cpp
	StackDbLockUnlocker.cpp
	TableLevelLock.cpp
	WriteLockHandle.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db engine_lock)

