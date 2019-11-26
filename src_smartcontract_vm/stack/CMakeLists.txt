

set(__src
	StackPopper.cpp
	VmStack.cpp
	VmStackManager.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm stack)

