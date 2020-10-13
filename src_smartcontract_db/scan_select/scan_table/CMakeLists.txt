

set(__src
	AbstractJoinScanTarget.cpp
	AbstractScanTableTarget.cpp
	CrossJoinScanTarget.cpp
	InnerJoinScanTarget.cpp
	LeftOuterJoinTarget.cpp
	ParenthesisScanTarget.cpp
	RightOuterJoinScanTarget.cpp
	TableScanTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_table)

