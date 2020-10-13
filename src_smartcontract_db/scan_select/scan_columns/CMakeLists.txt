

set(__src
	AbstractScanColumnsTarget.cpp
	AllScanColumns.cpp
	ScanColumn.cpp
	ScanColumnHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_columns)

