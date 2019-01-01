/*
 * NetworkShardStatus.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "bc_network/NetworkShardsStatus.h"

#include "bc_network/NetworkShard.h"

namespace codablecash {

NetworkShardsStatus::NetworkShardsStatus(int numShard) {
	this->numShard = numShard;
}

NetworkShardsStatus::~NetworkShardsStatus() {
}


} /* namespace codablecash */
