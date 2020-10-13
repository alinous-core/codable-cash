/*
 * AbstractJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "trx/transaction_scanner_join/AbstractJoinExecutor.h"

#include "trx/transaction_scanner_join/IJoinLeftSource.h"
#include "trx/transaction_scanner_join/IJoinRightSource.h"

#include "scan_select/scan_planner/scanner/ctx/ScanJoinContext.h"

#include "trx/transaction_scan_result/ScanResultFieldMetadata.h"


namespace codablecash {

AbstractJoinExecutor::AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultFieldMetadata* metadata, ScanJoinContext* context) {
	this->left = left;
	this->right = right;
	this->metadata = metadata;
	this->context = context;
}

AbstractJoinExecutor::~AbstractJoinExecutor() {
	delete this->left;
	delete this->right;
	delete this->metadata;
	delete this->context;
}

} /* namespace codablecash */
