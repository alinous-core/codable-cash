

set(__src
	CatchStatement.cpp
	FinallyStatement.cpp
	ThrowStatement.cpp
	TryStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_statement_exception)

