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

	ByteBuffer* pub = Schnorr::toByteBuffer(*key->publicKey);
	ByteBuffer* sec = Schnorr::toByteBuffer(*key->secretKey);
	address->pubkey = pub;
	address->secretkey = sec;

	address->shardhash = shard->getRandomHash();

	return address;
}

AbstractAddress* BlockchainAddress::clone() const noexcept {
	BlockchainAddress* addr = new BlockchainAddress();
	addr->shardhash = this->shardhash;
	if(this->pubkey != nullptr){
		addr->pubkey = this->pubkey->clone();
	}
	if(this->secretkey != nullptr){
		addr->secretkey = this->secretkey->clone();
	}

	return addr;
}

int BlockchainAddress::binarySize() const noexcept(false) {
	int total = sizeof(this->shardhash);

	total += sizeof(char);
	if(this->pubkey != nullptr){
		total += sizeof(int32_t);
		total += this->pubkey->capacity() * sizeof(uint8_t);
	}
	total += sizeof(char);
	if(this->secretkey != nullptr){
		total += sizeof(int32_t);
		total += this->secretkey->capacity() * sizeof(uint8_t);
	}

	return total;
}

void BlockchainAddress::toBinary(ByteBuffer* out) const noexcept(false) {
	out->put(this->shardhash);

	char isnotnull = (this->pubkey != nullptr) ? 1 : 0;
	out->put(isnotnull);
	if(isnotnull > 0){
		const uint8_t* ar = this->pubkey->array();
		int cap = this->pubkey->capacity();
		out->putInt(cap);
		out->put(ar, cap);
	}

	isnotnull = (this->secretkey != nullptr) ? 1 : 0;
	out->put(isnotnull);
	if(isnotnull > 0){
		const uint8_t* ar = this->secretkey->array();
		int cap = this->secretkey->capacity();
		out->putInt(cap);
		out->put(ar, cap);
	}
}

BlockchainAddress* BlockchainAddress::fromBinary(ByteBuffer* in) noexcept(false) {
	BlockchainAddress* address = new BlockchainAddress();

	address->shardhash = in->get();

	char isnotnull = in->get();
	if(isnotnull > 0){
		int cap = in->getInt();
		uint8_t* ar = new uint8_t[cap];
		StackArrayRelease<uint8_t> __st_ar(ar);

		in->get(ar, cap);

		address->pubkey = ByteBuffer::wrapWithEndian(ar, cap, true);
	}

	isnotnull = in->get();
	if(isnotnull > 0){
		int cap = in->getInt();
		uint8_t* ar = new uint8_t[cap];
		StackArrayRelease<uint8_t> __st_ar(ar);

		in->get(ar, cap);

		address->secretkey = ByteBuffer::wrapWithEndian(ar, cap, true);
	}

	return address;

}

bool BlockchainAddress::equals(const AbstractAddress* other) const noexcept {
	if(getType() != other->getType()){
		return false;
	}

	const BlockchainAddress* addr = dynamic_cast<const BlockchainAddress*>(other);

	if(this->shardhash != addr->shardhash){
		return false;
	}

	return (this->pubkey->binaryEquals(addr->pubkey)) &&
			(
					(this->secretkey == nullptr && addr->secretkey == nullptr) ||
					(this->secretkey != nullptr && addr->secretkey != nullptr && this->secretkey->binaryEquals(addr->secretkey))	);
}

IBlockObject* BlockchainAddress::copyData() const noexcept {
	// FIXME copyData()
	return nullptr;
}

} /* namespace codablecash */
