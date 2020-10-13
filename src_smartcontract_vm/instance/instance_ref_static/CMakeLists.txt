

set(__src
	LongIntegerKey.cpp
	NumericConstHolder.cpp
	StaticInstanceHolder.cpp
	StringConstHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_ref_static)

