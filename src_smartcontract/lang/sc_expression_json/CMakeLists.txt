

set(__src
	AbstractJsonExpression.cpp
	JsonArrayExpression.cpp
	JsonInitializerExpression.cpp
	JsonKeyValuePairExpression.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_expression_json)

