/*
 * test_address.cpp
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "bc_base/BlockchainAddress.h"
#include "bc_network/NetworkShardsStatus.h"
#include "base_io/ReverseByteBuffer.h"
#include "base/StackRelease.h"

#include "blockchain/DummyAddress.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestBlockchainAddressGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestBlockchainAddressGroup, constract){
	NetworkShardsStatus* shards = new NetworkShardsStatus(8);
	StackRelease<NetworkShardsStatus> __st_shards(shards);

	CHECK(shards->size() == 8)

	NetworkShard* shard = shards->getShard(1);
	BlockchainAddress* address = BlockchainAddress::createAddress(shard);
	StackRelease<BlockchainAddress> __st_address(address);

	int type = address->getType();
	CHECK(type == AbstractAddress::NORMAL_ADDRESS)
}

TEST(TestBlockchainAddressGroup, binary){
	NetworkShardsStatus* shards = new NetworkShardsStatus(8);
	StackRelease<NetworkShardsStatus> __st_shards(shards);

	CHECK(shards->size() == 8)

	NetworkShard* shard = shards->getShard(1);
	BlockchainAddress* address = BlockchainAddress::createAddress(shard);
	StackRelease<BlockchainAddress> __st_address(address);

	int size = address->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true);
	StackRelease<ByteBuffer> __st_buff(buff);

	address->toBinary(buff);

	buff->position(0);

	BlockchainAddress* address2 = BlockchainAddress::fromBinary(buff);
	StackRelease<BlockchainAddress> __st_address2(address2);

	bool res = address->equals(address2);
	CHECK(res)
}

TEST(TestBlockchainAddressGroup, equals_not){
	NetworkShardsStatus* shards = new NetworkShardsStatus(8);
	StackRelease<NetworkShardsStatus> __st_shards(shards);

	CHECK(shards->size() == 8)

	NetworkShard* shard = shards->getShard(1);
	BlockchainAddress* address = BlockchainAddress::createAddress(shard);
	StackRelease<BlockchainAddress> __st_address(address);

	BlockchainAddress* address2 = BlockchainAddress::createAddress(shards->getShard(0));
	StackRelease<BlockchainAddress> __st_address2(address2);

	bool res = address->equals(address2);
	CHECK(!res)

	DummyAddress daddr;
	res = address->equals(&daddr);
	CHECK(!res)
}



