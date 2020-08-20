

set(__src
	AbstractLogicalScanColumnTarget.cpp
	AndLogicalScanColumnTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns_logical)

