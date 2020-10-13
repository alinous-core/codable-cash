

set(__src
	MethodArgumentSetupper.cpp
	StackPopper.cpp
	VmStack.cpp
	VmStackManager.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm vm/stack)

