

set(__src
	CatchStatement.cpp
	ThrowStatement.cpp
	TryStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_statement_ctrl)

