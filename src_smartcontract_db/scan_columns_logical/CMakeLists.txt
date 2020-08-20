

set(__src
	AbstractLogicalScanColumn.cpp
	AndLogicalScanColumn.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns_logical)

