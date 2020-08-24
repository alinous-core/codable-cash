/*
 * AbstractJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "transaction_scanner_join/AbstractJoinExecutor.h"

#include "transaction_scanner_join/IJoinLeftSource.h"
#include "transaction_scanner_join/IJoinRightSource.h"

#include "transaction_scan_result/ScanResultFieldMetadata.h"

namespace codablecash {

AbstractJoinExecutor::AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultFieldMetadata* metadata) {
	this->left = left;
	this->right = right;
	this->metadata = metadata;
}

AbstractJoinExecutor::~AbstractJoinExecutor() {
	delete this->left;
	delete this->right;
	delete this->metadata;
}

} /* namespace codablecash */
