

set(__src
	AbstractVariableInstraction.cpp
	ExpressionAccess.cpp
	StackVariableAccess.cpp
	ThisPointerAccess.cpp
	VariableInstractionHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm variable_access)

