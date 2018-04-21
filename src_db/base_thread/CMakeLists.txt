set(__src
	AbstractThreadRunner.cpp
	SysMutex.cpp
	SysThread.cpp
)

handle_sub(codablecashlib "${__src}" db base_thread)

