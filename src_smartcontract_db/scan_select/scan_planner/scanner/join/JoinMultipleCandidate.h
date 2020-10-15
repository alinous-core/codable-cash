/*
 * JoinMuntipleCandidate.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidateCollection.h"

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class JoinCandidate;

class JoinMultipleCandidate : public AbstractJoinCandidateCollection {
public:
	JoinMultipleCandidate(const JoinMultipleCandidate& inst);
	explicit JoinMultipleCandidate(int joinType);
	virtual ~JoinMultipleCandidate();

	virtual AbstractJoinCandidate* multiply(const AbstractJoinCandidate* other) const noexcept;
	virtual AbstractJoinCandidate::CandidateType getCandidateType() const noexcept;
	virtual int size() const noexcept;
	virtual const JoinCandidate* get(int i) const noexcept;
	virtual AbstractJoinCandidate* copy() const noexcept;

	void mul(const JoinCandidate* candidate) noexcept;

	virtual int getOverHeadScore() const noexcept;
private:
	ArrayList<JoinCandidate> list;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINMUNTIPLECANDIDATE_H_ */
