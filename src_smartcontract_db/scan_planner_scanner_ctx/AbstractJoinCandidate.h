/*
 * AbstractJoinCandidate.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_ABSTRACTJOINCANDIDATE_H_
#define SCAN_PLANNER_SCANNER_CTX_ABSTRACTJOINCANDIDATE_H_

namespace codablecash {

class AbstractJoinCandidate {
public:
	static const constexpr int LEFT_OUTER{1};
	static const constexpr int INNER{2};

	explicit AbstractJoinCandidate(int joinType);
	virtual ~AbstractJoinCandidate();

protected:
	int joinType;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_ABSTRACTJOINCANDIDATE_H_ */
