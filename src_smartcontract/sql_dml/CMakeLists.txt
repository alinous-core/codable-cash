

set(__src
	BeginStatement.cpp
	CommitStatement.cpp
	DeleteStatement.cpp
	InsertStatement.cpp
	RollbackStatement.cpp
	SelectStatement.cpp
	UpdateStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sql_dml)

