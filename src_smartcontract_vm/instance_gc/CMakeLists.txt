

set(__src
	GcManager.cpp
	ReferenceStatus.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_gc)

