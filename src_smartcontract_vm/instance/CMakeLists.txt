

set(__src
	AbstractVmInstance.cpp
	IInstanceContainer.cpp
	VmClassInstance.cpp
	VmInstanceTypesConst.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance)

