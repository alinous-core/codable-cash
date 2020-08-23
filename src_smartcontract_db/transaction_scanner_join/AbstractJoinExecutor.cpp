/*
 * AbstractJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "transaction_scanner_join/AbstractJoinExecutor.h"

#include "transaction_scanner_join/IJoinLeftSource.h"
#include "transaction_scanner_join/IJoinRightSource.h"

namespace codablecash {

AbstractJoinExecutor::AbstractJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right) {
	this->left = left;
	this->right = right;
}

AbstractJoinExecutor::~AbstractJoinExecutor() {
	delete this->left;
	delete this->right;
}

} /* namespace codablecash */
