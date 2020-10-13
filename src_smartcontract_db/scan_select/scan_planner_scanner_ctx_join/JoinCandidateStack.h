/*
 * JoinCandidateStack.h
 *
 *  Created on: 2020/09/03
 *      Author: iizuka
 */

#ifndef SCAN_PLANNER_SCANNER_CTX_JOIN_JOINCANDIDATESTACK_H_
#define SCAN_PLANNER_SCANNER_CTX_JOIN_JOINCANDIDATESTACK_H_

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

using alinous::ArrayList;
using alinous::RawArrayPrimitive;

namespace codablecash {

class AbstractJoinCandidate;

class JoinCandidateStack {
public:
	JoinCandidateStack();
	virtual ~JoinCandidateStack();

	bool isEmpty() const noexcept;
	void push(AbstractJoinCandidate* candidate) noexcept;
	AbstractJoinCandidate* pop() noexcept;

	void mark() noexcept;
	void unmark() noexcept;
private:
	ArrayList<AbstractJoinCandidate> stack;
	RawArrayPrimitive<int> markStack;

};

} /* namespace codablecash */

#endif /* SCAN_PLANNER_SCANNER_CTX_JOIN_JOINCANDIDATESTACK_H_ */
