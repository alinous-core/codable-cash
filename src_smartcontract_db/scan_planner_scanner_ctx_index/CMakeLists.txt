

set(__src
	AbstractIndexCandidate.cpp
	IndexCandidate.cpp
	TableIndexDetector.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner_scanner_ctx_index)

