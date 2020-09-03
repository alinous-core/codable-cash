/*
 * JoinBranchCandidate.h
 *
 *  Created on: 2020/09/01
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINBRANCHCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINBRANCHCANDIDATE_H_

#include "scan_planner_scanner_ctx_join/AbstractJoinCandidate.h"

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class JoinCandidate;

class JoinOrCandidate : public AbstractJoinCandidate {
public:
	explicit JoinOrCandidate(int joinType);
	virtual ~JoinOrCandidate();

	virtual AbstractJoinCandidate::CandidateType getCandidateType() const noexcept;
	virtual AbstractJoinCandidate* multiply(const AbstractJoinCandidate* other) const noexcept;

private:
	ArrayList<JoinCandidate> list;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINBRANCHCANDIDATE_H_ */
