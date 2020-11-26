

set(__src
	AbstractColumnsIndexWrapper.cpp
	IndexResolver.cpp
	MultipleColumnIndex.cpp
	SingleColumnIndex.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_planner/scanner/index_resolv)

