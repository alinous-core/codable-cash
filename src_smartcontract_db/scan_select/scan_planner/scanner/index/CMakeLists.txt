

set(__src
	AbstractIndexCandidate.cpp
	AbstractIndexCandidateCollection.cpp
	IndexCandidate.cpp
	IndexRangeCandidate.cpp
	MultipleIndexCandidate.cpp
	OrIndexCandidate.cpp
	TableIndexDetector.cpp
	TableIndexDetectorStack.cpp
	TableIndexDetectorStackMarker.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_planner/scanner/index)

