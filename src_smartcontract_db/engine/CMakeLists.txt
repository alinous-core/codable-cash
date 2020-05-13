

set(__src
	CdbException.cpp
	CdbOid.cpp
	CodableDatabase.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db engine)

