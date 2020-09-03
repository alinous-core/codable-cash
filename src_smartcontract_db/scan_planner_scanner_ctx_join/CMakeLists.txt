

set(__src
	AbstractJoinCandidate.cpp
	JoinCandidate.cpp
	JoinCandidateHolder.cpp
	JoinCandidateStack.cpp
	JoinCandidateStackMarker.cpp
	JoinMultipleCandidate.cpp
	JoinOrCandidate.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner_scanner_ctx_join)

