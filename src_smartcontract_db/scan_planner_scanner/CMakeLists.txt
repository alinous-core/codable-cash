

set(__src
	AbstractScannerFactory.cpp
	TableScannerFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner_scanner)

