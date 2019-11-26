

set(__src
	LongIntegerKey.cpp
	NumericConstHolder.cpp
	StaticInstanceHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_ref_static)

