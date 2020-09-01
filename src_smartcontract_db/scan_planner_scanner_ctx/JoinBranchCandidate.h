/*
 * JoinBranchCandidate.h
 *
 *  Created on: 2020/09/01
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINBRANCHCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINBRANCHCANDIDATE_H_

#include "scan_planner_scanner_ctx/AbstractJoinCandidate.h"

namespace codablecash {

class JoinBranchCandidate : public AbstractJoinCandidate {
public:
	explicit JoinBranchCandidate(int joinType);
	virtual ~JoinBranchCandidate();
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINBRANCHCANDIDATE_H_ */
