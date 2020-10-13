/*
 * JoinCandidateStackMarker.h
 *
 *  Created on: 2020/09/03
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOIN_JOINCANDIDATESTACKMARKER_H_
#define SCAN_PLANNER_SCANNER_CTX_JOIN_JOINCANDIDATESTACKMARKER_H_

namespace codablecash {

class JoinCandidateStack;

class JoinCandidateStackMarker {
public:
	explicit JoinCandidateStackMarker(JoinCandidateStack* stack);
	virtual ~JoinCandidateStackMarker();

private:
	JoinCandidateStack* stack;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOIN_JOINCANDIDATESTACKMARKER_H_ */
