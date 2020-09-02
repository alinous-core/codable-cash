/*
 * JoinCandidateHolder.h
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATEHOLDER_H_
#define SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATEHOLDER_H_

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class AbstractJoinCandidate;
class AbstractScanTableTarget;

class JoinCandidateHolder {
public:
	JoinCandidateHolder(const AbstractScanTableTarget* left, const AbstractScanTableTarget* right);
	virtual ~JoinCandidateHolder();

	bool isEmpty() const noexcept;
	void push(AbstractJoinCandidate* candidate) noexcept;
	AbstractJoinCandidate* pop() noexcept;

private:
	ArrayList<AbstractJoinCandidate> stack;

	const AbstractScanTableTarget* left;
	const AbstractScanTableTarget* right;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATEHOLDER_H_ */
