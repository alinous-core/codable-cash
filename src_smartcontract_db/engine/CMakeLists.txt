

set(__src
	CodableDatabase.cpp
	DatabaseException.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db engine)

