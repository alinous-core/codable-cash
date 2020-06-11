

set(__src
	AbstractRecordScanner.cpp
	IndexScanner.cpp
	RangeScanner.cpp
	RecordScanner.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan)

