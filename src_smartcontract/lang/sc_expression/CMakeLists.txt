

set(__src
	AbstractBinaryExpression.cpp
	AbstractExpression.cpp
	AllocationExpression.cpp
	ArrayReferenceExpression.cpp
	CastExpression.cpp
	ConstructorArray.cpp
	ConstructorCall.cpp
	FunctionCallExpression.cpp
	MemberReferenceExpression.cpp
	ParenthesisExpression.cpp
	VariableIdentifier.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_expression)

