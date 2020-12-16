/*
 * AbstractJoinCandidate.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_ABSTRACTJOINCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_ABSTRACTJOINCANDIDATE_H_

namespace codablecash {

class AbstractScanTableTarget;
class CdbTableIndex;

class AbstractJoinCandidate {
public:
	static const constexpr int LEFT_OUTER{1};
	static const constexpr int INNER{2};

	enum CandidateType{
		EQUALS,
		AND,
		OR
	};

	explicit AbstractJoinCandidate(int joinType);
	virtual ~AbstractJoinCandidate();

	int getJoinType() const noexcept {
		return joinType;
	}

	virtual CandidateType getCandidateType() const noexcept = 0;
	virtual AbstractJoinCandidate* multiply(const AbstractJoinCandidate* other) const noexcept = 0;
	virtual AbstractJoinCandidate* copy() const noexcept = 0;

	virtual int getOverHeadScore(AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept = 0;

	virtual CdbTableIndex* getIndex() const noexcept = 0;

protected:
	int joinType;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_ABSTRACTJOINCANDIDATE_H_ */
