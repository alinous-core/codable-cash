/*
 * OuterJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join/OuterJoinExecutor.h"

namespace codablecash {

OuterJoinExecutor::OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultFieldMetadata* metadata, ScanJoinContext* context)
					: AbstractJoinExecutor(left, right, metadata, context){

}

OuterJoinExecutor::~OuterJoinExecutor() {

}

} /* namespace codablecash */
