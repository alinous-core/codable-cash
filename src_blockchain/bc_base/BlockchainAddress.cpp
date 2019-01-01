/*
 * BlockchainAddress.cpp
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#include "bc_base/BlockchainAddress.h"
#include "bc_network/NetworkShard.h"

namespace codablecash {

BlockchainAddress::BlockchainAddress() {
	this->shardhash = 0;
	this->pubkey32 = nullptr;
}

BlockchainAddress::~BlockchainAddress() {
	if(this->pubkey32 != nullptr){
		delete [] this->pubkey32;
	}
}

BlockchainAddress* BlockchainAddress::createAddress(NetworkShard* shard) noexcept {
	BlockchainAddress* address = new BlockchainAddress();

	return address;
}

} /* namespace codablecash */
