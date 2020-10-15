/*
 * ScanJoinContextHolder.cpp
 *
 *  Created on: 2020/08/30
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContextHolder.h"

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContext.h"

namespace codablecash {

ScanJoinContextHolder::ScanJoinContextHolder() {

}

ScanJoinContextHolder::~ScanJoinContextHolder() {
	this->list.deleteElements();
}

} /* namespace codablecash */
