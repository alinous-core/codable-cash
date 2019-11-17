

set(__src
	AbstractFunctionExtArguments.cpp
	NullArgument.cpp
	NumericArgument.cpp
	StringArgument.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm ext_arguments)

