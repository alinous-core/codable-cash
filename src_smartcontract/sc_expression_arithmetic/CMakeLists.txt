

set(__src
	AbstractArithmeticBinaryExpresson.cpp
	AddExpression.cpp
	MultiplicativeExpression.cpp
	NegateExpression.cpp
	PostIncrementExpression.cpp
	PreIncrementExpression.cpp
	ZeroDivisionException.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_expression_arithmetic)

