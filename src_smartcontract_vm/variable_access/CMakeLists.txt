

set(__src
	AbstractVariableInstraction.cpp
	ArrayReferenceAccess.cpp
	ExpressionAccess.cpp
	FunctionArguments.cpp
	MemberFunctionCallAccess.cpp
	MemberVariableAccess.cpp
	StackVariableAccess.cpp
	ThisPointerAccess.cpp
	VariableInstractionHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm variable_access)

