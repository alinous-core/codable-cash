

set(__src
	AbstractScanColumns.cpp
	AllScanColumns.cpp
	ExpressionScanColumn.cpp
	ScanColumn.cpp
	ScanColumnHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns)

