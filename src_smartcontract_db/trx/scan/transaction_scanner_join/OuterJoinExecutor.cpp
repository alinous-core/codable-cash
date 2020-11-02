/*
 * OuterJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join/OuterJoinExecutor.h"

namespace codablecash {

OuterJoinExecutor::OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right, ScanResultMetadata* metadata, ScanJoinContext* context)
					: AbstractJoinExecutor(left, right, metadata, context){

}

OuterJoinExecutor::~OuterJoinExecutor() {
	shutdown();
}

void OuterJoinExecutor::start() {
}

bool OuterJoinExecutor::hasNext() {
	return false;
}

const CdbRecord* OuterJoinExecutor::next() {
	return nullptr;
}

void OuterJoinExecutor::shutdown() {
}


} /* namespace codablecash */
