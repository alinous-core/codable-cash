

set(__src
	ClassTypeReference.cpp
	StaticClassEntry.cpp
	StaticClassReferenceHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_ref_class_static)

