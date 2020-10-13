

set(__src
	AbstractReference.cpp
	ConstStaticPrimitive.cpp
	ObjectReference.cpp
	PrimitiveReference.cpp
	RefereceFactory.cpp
	VmRootReference.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_ref)

