

set(__src
	AbstractReference.cpp
	ObjectReference.cpp
	PrimitiveReference.cpp
	RefereceFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_ref)

