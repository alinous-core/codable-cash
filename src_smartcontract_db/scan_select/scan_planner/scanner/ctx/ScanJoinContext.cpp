/*
 * ScanJoinContext.cpp
 *
 *  Created on: 2020/08/29
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContext.h"

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"

namespace codablecash {

ScanJoinContext::ScanJoinContext(const AbstractJoinCandidate* joinCandidate) {
	this->joinCandidate = joinCandidate->copy();
}

ScanJoinContext::~ScanJoinContext() {
	delete this->joinCandidate;
}

} /* namespace codablecash */
