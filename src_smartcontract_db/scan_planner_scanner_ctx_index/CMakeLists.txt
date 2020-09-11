

set(__src
	AbstractIndexCandidate.cpp
	IndexCandidate.cpp
	MultipleIndexCandidate.cpp
	OrIndexCandidate.cpp
	TableIndexDetector.cpp
	TableIndexDetectorStack.cpp
	TableIndexDetectorStackMarker.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner_scanner_ctx_index)

