/*
 * InnerJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "transaction_scanner_join/InnerJoinExecutor.h"

namespace codablecash {

InnerJoinExecutor::InnerJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right)
		: AbstractJoinExecutor(left, right){

}

InnerJoinExecutor::~InnerJoinExecutor() {

}

} /* namespace codablecash */
