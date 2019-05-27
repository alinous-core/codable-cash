

set(__src
	AbstractVmInstance.cpp
	VmArrayInstance.cpp
	VmClassInstance.cpp
	VmInstanceStack.cpp
	VmStringInstance.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance)

