

set(__src
	GcCyclicCheckerContext.cpp
	GcManager.cpp
	ReferenceStatus.cpp
	ReferenceStatusCompare.cpp
	StackFloatingVariableHandler.cpp
	VmInstanceKey.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_gc)

