

set(__src
	AbstractExpression.cpp
	AllocationExpression.cpp
	ArrayReferenceExpression.cpp
	BooleanLiteral.cpp
	CastExpression.cpp
	FunctionCallExpression.cpp
	LiteralExpression.cpp
	MemberReferenceExpression.cpp
	NullLiteral.cpp
	NumberLiteral.cpp
	ParenthesisExpression.cpp
	VariableIdentifier.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_expression)

