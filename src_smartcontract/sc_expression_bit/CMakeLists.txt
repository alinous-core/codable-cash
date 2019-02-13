

set(__src
	AndExpression.cpp
	BitReverseExpression.cpp
	ExclusiveOrExpression.cpp
	OrExpression.cpp
	ShiftExpression.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_expression_bit)

