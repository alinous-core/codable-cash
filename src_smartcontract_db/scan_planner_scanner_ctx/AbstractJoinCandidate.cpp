/*
 * AbstractJoinCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx/AbstractJoinCandidate.h"

namespace codablecash {

AbstractJoinCandidate::AbstractJoinCandidate(int joinType) {
	this->joinType = joinType;
}

AbstractJoinCandidate::~AbstractJoinCandidate() {

}

} /* namespace codablecash */
