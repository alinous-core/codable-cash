

set(__src
	AbstractVmInstance.cpp
	VmClassInstance.cpp
	VmInstanceStack.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance)

