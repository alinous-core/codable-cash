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
class JoinCandidate;
class JoinCandidateStack;

class JoinCandidateHolder {
public:
	JoinCandidateHolder(const AbstractScanTableTarget* left, const AbstractScanTableTarget* right);
	virtual ~JoinCandidateHolder();

	bool isEmpty() const noexcept;
	void push(AbstractJoinCandidate* candidate) noexcept;
	AbstractJoinCandidate* pop() noexcept;
	JoinCandidateStack* getStack() const noexcept {
		return stack;
	}

	bool isJoinCondition(JoinCandidate* candidate) const noexcept;
	void addJoinCandidate(AbstractJoinCandidate* candidate) noexcept;

	bool isInnerJoin() const noexcept;

	const AbstractJoinCandidate* getBestCandidate(AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept;

	const AbstractScanTableTarget* getLeft() const noexcept {
		return left;
	}

	const AbstractScanTableTarget* getRight() const noexcept {
		return right;
	}

private:
	const AbstractJoinCandidate* getBestFromList(const ArrayList<AbstractJoinCandidate>* list,
			AbstractScanTableTarget* left, AbstractScanTableTarget* right) const noexcept;

private:
	JoinCandidateStack* stack;

	ArrayList<AbstractJoinCandidate> leftOuterJoin;
	ArrayList<AbstractJoinCandidate> innerJoin;

	const AbstractScanTableTarget* left;
	const AbstractScanTableTarget* right;
};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOINCANDIDATEHOLDER_H_ */
