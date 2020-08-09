

set(__src
	AbstractJoinScanTarget.cpp
	AbstractScanTableTarget.cpp
	CrossJoinScanTarget.cpp
	InnerJoinScanTarget.cpp
	LeftOuterJoinTarget.cpp
	TableScanTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_table)

