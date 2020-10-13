

set(__src
	ArrayReference.cpp
	VmArrayInstance.cpp
	VmArrayInstanceUtils.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_array)

