/*
 * JoinCandidateStack.cpp
 *
 *  Created on: 2020/09/03
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/join/JoinCandidateStack.h"
#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"

namespace codablecash {

JoinCandidateStack::JoinCandidateStack() : markStack(4) {

}

JoinCandidateStack::~JoinCandidateStack() {
	this->stack.deleteElements();
}

bool JoinCandidateStack::isEmpty() const noexcept {
	if(this->markStack.size() == 0){
		return this->stack.isEmpty();
	}

	int topidx = this->markStack.size() - 1;
	int index = this->markStack.get(topidx);

	return this->stack.size() == index;
}

void JoinCandidateStack::push(AbstractJoinCandidate* candidate) noexcept {
	this->stack.addElement(candidate);
}

AbstractJoinCandidate* JoinCandidateStack::pop() noexcept {
	int index = this->stack.size() - 1;
	return this->stack.remove(index);
}

void JoinCandidateStack::mark() noexcept {
	int index = this->stack.size();
	this->markStack.addElement(index);
}

void JoinCandidateStack::unmark() noexcept {
	int index = this->markStack.size() - 1;
	this->markStack.remove(index);
}

} /* namespace codablecash */
