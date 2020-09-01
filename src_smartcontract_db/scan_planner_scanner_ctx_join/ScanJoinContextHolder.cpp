/*
 * ScanJoinContextHolder.cpp
 *
 *  Created on: 2020/08/30
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/ScanJoinContextHolder.h"

#include "scan_planner_scanner_ctx/ScanJoinContext.h"

namespace codablecash {

ScanJoinContextHolder::ScanJoinContextHolder() {

}

ScanJoinContextHolder::~ScanJoinContextHolder() {
	this->list.deleteElements();
}

} /* namespace codablecash */
