

set(__src
	AbstractScanTableTarget.cpp
	TableScanTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_table)

