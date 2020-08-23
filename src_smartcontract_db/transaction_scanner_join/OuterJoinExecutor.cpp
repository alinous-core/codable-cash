/*
 * OuterJoinExecutor.cpp
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#include "transaction_scanner_join/OuterJoinExecutor.h"

namespace codablecash {

OuterJoinExecutor::OuterJoinExecutor(IJoinLeftSource* left, IJoinRightSource* right)
					: AbstractJoinExecutor(left, right){

}

OuterJoinExecutor::~OuterJoinExecutor() {

}

} /* namespace codablecash */
