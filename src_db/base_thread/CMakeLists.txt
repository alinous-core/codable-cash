set(__src
	AbstractThreadRunner.cpp
	ConcurrentGate.cpp
	ILock.cpp
	LockCondition.cpp
	StackUnlocker.cpp
	SynchronizedLock.cpp
	SysMutex.cpp
	SysThread.cpp
)

handle_sub(codablecashlib "${__src}" db base_thread)

