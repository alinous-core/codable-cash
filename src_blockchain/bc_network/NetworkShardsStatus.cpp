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

	int shardsize = NetworkShardsStatus::MAX_SHARD_HASH / numShard;
	for(int i = 0; i != numShard; ++i){
		NetworkShard* shard = new NetworkShard(i * shardsize, shardsize);
		this->shards.addElement(shard);
	}
}

NetworkShardsStatus::~NetworkShardsStatus() {
	int maxLoop = this->shards.size();
	for(int i = 0; i != maxLoop; ++i){
		NetworkShard* shard = this->shards.get(i);
		delete shard;
	}
}

int NetworkShardsStatus::size() const noexcept {
	return this->shards.size();
}

NetworkShard* NetworkShardsStatus::getShard(int pos) const noexcept {
	return this->shards.get(pos);
}

} /* namespace codablecash */


