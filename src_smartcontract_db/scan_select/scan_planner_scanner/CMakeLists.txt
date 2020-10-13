

set(__src
	AbstractJoinScannerFactory.cpp
	AbstractScannerFactory.cpp
	CrossJoinScanerFactory.cpp
	InnerJoinScannerFactory.cpp
	LeftJoinScannerFactory.cpp
	TableScannerFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_planner_scanner)

