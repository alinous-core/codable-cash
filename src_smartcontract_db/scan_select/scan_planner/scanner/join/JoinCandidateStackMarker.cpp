/*
 * JoinCandidateStackMarker.cpp
 *
 *  Created on: 2020/09/03
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/join/JoinCandidateStackMarker.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidateStack.h"

namespace codablecash {

JoinCandidateStackMarker::JoinCandidateStackMarker(JoinCandidateStack* stack) {
	stack->mark();
	this->stack = stack;
}

JoinCandidateStackMarker::~JoinCandidateStackMarker() {
	this->stack->unmark();
}

} /* namespace codablecash */
