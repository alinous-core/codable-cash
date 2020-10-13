

set(__src
	StaticClassMetadata.cpp
	StaticClassMetadataHolder.cpp
	StaticVariableMetadata.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_ref_class_static_meta)

