

set(__src
	AbstractRecordScanner.cpp
	IndexScanner.cpp
	RangeScanner.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan)

