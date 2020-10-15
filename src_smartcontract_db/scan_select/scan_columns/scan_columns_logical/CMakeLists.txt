

set(__src
	AbstractLogicalScanColumnTarget.cpp
	AndScanColumnTarget.cpp
	NotScanColumnTarget.cpp
	OrScanColumnTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_columns/scan_columns_logical)

