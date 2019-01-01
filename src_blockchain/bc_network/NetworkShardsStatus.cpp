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

int NetworkShardsStatus::binarySize() const {
	return 0;
}

void NetworkShardsStatus::toBinary(ByteBuffer* out) const {
}

} /* namespace codablecash */
