

set(__src
	AbstractBinaryExpression.cpp
	AbstractExpression.cpp
	AllocationExpression.cpp
	ArrayReferenceExpression.cpp
	BooleanLiteral.cpp
	CastExpression.cpp
	ConstructorArray.cpp
	ConstructorCall.cpp
	FunctionCallExpression.cpp
	LiteralExpression.cpp
	MemberReferenceExpression.cpp
	NullLiteral.cpp
	NumberLiteral.cpp
	ParenthesisExpression.cpp
	VariableIdentifier.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_expression)

