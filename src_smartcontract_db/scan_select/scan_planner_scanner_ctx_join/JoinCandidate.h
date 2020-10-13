/*
 * JoinCandidate.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATE_H_

#include "scan_select/scan_planner_scanner_ctx_join/AbstractJoinCandidateCollection.h"

namespace codablecash {

class AbstractJoinScanTarget;
class ColumnIdentifierScanParam;
class AbstractScanTableTarget;

class JoinCandidate : public AbstractJoinCandidateCollection {
public:
	JoinCandidate(const JoinCandidate& inst);
	explicit JoinCandidate(int joinType, ColumnIdentifierScanParam* left, ColumnIdentifierScanParam* right);
	virtual ~JoinCandidate();

	const AbstractScanTableTarget* getLeftTarget() const noexcept;
	const AbstractScanTableTarget* getRightTarget() const noexcept;

	virtual JoinCandidate::CandidateType getCandidateType() const noexcept;
	virtual AbstractJoinCandidate* multiply(const AbstractJoinCandidate* other) const noexcept;
	virtual int size() const noexcept;
	virtual const JoinCandidate* get(int i) const noexcept;
	virtual AbstractJoinCandidate* copy() const noexcept;

private:
	ColumnIdentifierScanParam* left;
	ColumnIdentifierScanParam* right;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATE_H_ */
