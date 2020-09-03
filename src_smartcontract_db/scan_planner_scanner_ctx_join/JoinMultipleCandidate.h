/*
 * JoinMuntipleCandidate.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_

#include "scan_planner_scanner_ctx_join/AbstractJoinCandidate.h"

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class JoinCandidate;

class JoinMultipleCandidate : public AbstractJoinCandidate {
public:
	explicit JoinMultipleCandidate(int joinType);
	virtual ~JoinMultipleCandidate();

	virtual AbstractJoinCandidate* multiply(const AbstractJoinCandidate* other) const noexcept;
	virtual AbstractJoinCandidate::CandidateType getCandidateType() const noexcept;

	void mul(const JoinCandidate* candidate) noexcept;
private:
	ArrayList<JoinCandidate> list;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_ */
