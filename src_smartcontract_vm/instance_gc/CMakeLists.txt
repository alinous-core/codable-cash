

set(__src
	GcCyclicCheckerContext.cpp
	GcManager.cpp
	ReferenceStatus.cpp
	VmInstanceKey.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_gc)

