/*
 * AbstractJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join/AbstractJoinExecutor.h"

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"
#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContext.h"

#include "trx/scan/transaction_scan_result/ScanResultMetadata.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

namespace codablecash {

AbstractJoinExecutor::AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata
		, ScanJoinContext* context, AbstractScanCondition* filterCondition) {
	this->left = left;
	this->right = right;
	this->metadata = new ScanResultMetadata(*metadata);
	this->context = context;
	this->filterCondition = filterCondition != nullptr ? filterCondition->cloneCondition() : nullptr;
}

AbstractJoinExecutor::~AbstractJoinExecutor() {
	delete this->left;
	delete this->right;
	delete this->metadata;
	delete this->context;
	delete this->filterCondition;
}

void AbstractJoinExecutor::start() {
	this->left->start();
	this->right->start();
}

void AbstractJoinExecutor::shutdown() {
	this->left->shutdown();
	this->right->shutdown();
}


} /* namespace codablecash */
