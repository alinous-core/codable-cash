

set(__src
	CatchStatement.cpp
	FinallyStatement.cpp
	ThrowStatement.cpp
	TryStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_statement_exception)

