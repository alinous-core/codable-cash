

set(__src
	AbstractRecordScanner.cpp
	IndexRecordScanner.cpp
	IndexScanner.cpp
	RangeChecker.cpp
	RecordScanner.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan)

