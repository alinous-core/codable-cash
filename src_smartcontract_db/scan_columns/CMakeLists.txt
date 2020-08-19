

set(__src
	AbstractScanColumns.cpp
	AllScanColumns.cpp
	ScanColumn.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns)

