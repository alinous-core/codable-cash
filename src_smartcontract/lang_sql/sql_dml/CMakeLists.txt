

set(__src
	BeginStatement.cpp
	CommitStatement.cpp
	DeleteStatement.cpp
	InsertStatement.cpp
	RollbackStatement.cpp
	SelectStatement.cpp
	UpdateStatement.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang_sql/sql_dml)

