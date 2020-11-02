/*
 * InnerJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join/InnerJoinExecutor.h"

namespace codablecash {

InnerJoinExecutor::InnerJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata, ScanJoinContext* context)
		: AbstractJoinExecutor(left, right, metadata, context){

}

InnerJoinExecutor::~InnerJoinExecutor() {

}

} /* namespace codablecash */
