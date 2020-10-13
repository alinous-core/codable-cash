

set(__src
	AbstractVariableInstraction.cpp
	ArrayReferenceAccess.cpp
	ClassTypeAccess.cpp
	ExpressionAccess.cpp
	FunctionArguments.cpp
	MemberFunctionCallAccess.cpp
	MemberVariableAccess.cpp
	StackVariableAccess.cpp
	ThisPointerAccess.cpp
	VariableInstractionHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm vm/variable_access)

