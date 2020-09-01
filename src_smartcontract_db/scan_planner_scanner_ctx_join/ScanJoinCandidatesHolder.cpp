/*
 * ScanJoinContextHolder.cpp
 *
 *  Created on: 2020/08/30
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/ScanJoinCandidatesHolder.h"

#include "scan_planner_scanner_ctx/ScanJoinContext.h"

namespace codablecash {

ScanJoinCandidatesHolder::ScanJoinCandidatesHolder() {

}

ScanJoinCandidatesHolder::~ScanJoinCandidatesHolder() {
	this->list.deleteElements();
}

} /* namespace codablecash */
