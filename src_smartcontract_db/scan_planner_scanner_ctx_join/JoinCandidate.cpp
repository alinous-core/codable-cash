/*
 * JoinCandidate.cpp
 *
 *  Created on: 2020/08/31
 *      Author: iizuka
 */

#include "scan_planner_scanner_ctx_join/JoinCandidate.h"

namespace codablecash {

JoinCandidate::JoinCandidate(int joinType, ColumnIdentifierScanParam* left, ColumnIdentifierScanParam* right) : AbstractJoinCandidate(joinType) {
	this->left = left;
	this->right = right;
}

JoinCandidate::~JoinCandidate() {
	this->left = nullptr;
	this->right = nullptr;
}

} /* namespace codablecash */
