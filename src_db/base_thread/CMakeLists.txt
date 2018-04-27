set(__src
	AbstractThreadRunner.cpp
	StackUnlocker.cpp
	SysMutex.cpp
	SysThread.cpp
)

handle_sub(codablecashlib "${__src}" db base_thread)

