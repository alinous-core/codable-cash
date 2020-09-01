

set(__src
	AbstractJoinCandidate.cpp
	JoinBranchCandidate.cpp
	JoinCandidate.cpp
	JoinCandidateHolder.cpp
	JoinMuntipleCandidate.cpp
	ScanJoinContextHolder.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_planner_scanner_ctx_join)

