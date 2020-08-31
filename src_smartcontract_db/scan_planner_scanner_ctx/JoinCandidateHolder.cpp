/*
 * JoinCandidateHolder.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx/JoinCandidateHolder.h"
#include "scan_planner_scanner_ctx/AbstractJoinCandidate.h"

namespace codablecash {

JoinCandidateHolder::JoinCandidateHolder() {

}

JoinCandidateHolder::~JoinCandidateHolder() {
	this->stack.deleteElements();
}

} /* namespace codablecash */
