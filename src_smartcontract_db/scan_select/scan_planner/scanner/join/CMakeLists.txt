

set(__src
	AbstractJoinCandidate.cpp
	AbstractJoinCandidateCollection.cpp
	JoinCandidate.cpp
	JoinCandidateHolder.cpp
	JoinCandidateStack.cpp
	JoinCandidateStackMarker.cpp
	JoinMultipleCandidate.cpp
	JoinOrCandidate.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_planner/scanner/join)

