

set(__src
	CdbException.cpp
	CodableDatabase.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db engine)

