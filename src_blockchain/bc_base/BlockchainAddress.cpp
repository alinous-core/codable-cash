/*
 * BlockchainAddress.cpp
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#include "bc_base/BlockchainAddress.h"
#include "bc_network/NetworkShard.h"
#include "crypto/Schnorr.h"
#include "base_io/ReverseByteBuffer.h"

#include "base/StackRelease.h"

namespace codablecash {

BlockchainAddress::BlockchainAddress() : AbstractAddress(AbstractAddress::NORMAL_ADDRESS) {
	this->shardhash = 0;
	this->pubkey = nullptr;
	this->secretkey = nullptr;
}

BlockchainAddress::~BlockchainAddress() {
	if(this->pubkey != nullptr){
		delete this->pubkey;
	}
	if(this->secretkey != nullptr){
		delete this->secretkey;
	}
}

BlockchainAddress* BlockchainAddress::createAddress(const NetworkShard* shard) noexcept {
	BlockchainAddress* address = new BlockchainAddress();

	SchnorrKeyPair* key = Schnorr::generateKey();
	StackRelease<SchnorrKeyPair> __st_key(key);

	ByteBuffer* pub = Schnorr::toByteBuffer(key->publicKey);
	ByteBuffer* sec = Schnorr::toByteBuffer(key->secretKey);
	address->pubkey = pub;
	address->secretkey = sec;


	return address;
}

} /* namespace codablecash */
