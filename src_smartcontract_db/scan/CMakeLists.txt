

set(__src
	AbstractRecordScanner.cpp
	IndexScanner.cpp
	RangeChecker.cpp
	RecordScanner.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan)

