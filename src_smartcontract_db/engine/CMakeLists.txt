

set(__src
	CdbBinaryObject.cpp
	CdbException.cpp
	CdbOid.cpp
	CodableDatabase.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db engine)

