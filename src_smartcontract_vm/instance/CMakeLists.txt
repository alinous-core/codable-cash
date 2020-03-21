

set(__src
	AbstractVmInstance.cpp
	AbstractVmInstanceSubstance.cpp
	IInstanceContainer.cpp
	VmAllocatee.cpp
	VmClassInstance.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance)

