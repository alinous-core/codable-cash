/*
 * test_shard_stat.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "base_io/ByteBuffer.h"
#include <algorithm>
#include "bc_network/NodeIdentifier.h"
#include "base/StackRelease.h"
#include "bc_network/NetworkShardsStatus.h"
#include "bc_network/NetworkShard.h"

#include "crypto/IKeyPair.h"
#include "test_utils/t_macros.h"


using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestShardStatGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestShardStatGroup, constract){
	NetworkShardsStatus* address = new NetworkShardsStatus(8);


	delete address;
}

TEST(TestShardStatGroup, clone){
	NetworkShardsStatus* address = new NetworkShardsStatus(8);
	NetworkShard* shard = address->getShard(2);

	NetworkShard* shard2 = shard->clone();

	delete shard2;
	delete address;
}

TEST(TestShardStatGroup, nodeid){
	NetworkShardsStatus* address = new NetworkShardsStatus(8); __STP(address);
	NetworkShard* shard = address->getShard(2);

	NodeIdentifier nodeId = NodeIdentifier::create(shard);
	NodeIdentifier nodeId2;

	nodeId2 = std::move(nodeId);
}

TEST(TestShardStatGroup, shardbinary){
	NetworkShardsStatus* address = new NetworkShardsStatus(8); __STP(address);
	NetworkShard* shard = address->getShard(2);

	int length = shard->binarySize();
	ByteBuffer* bshard = ByteBuffer::allocate(length); __STP(bshard);

	shard->toBinary(bshard);

	CHECK(length == bshard->position())

	bshard->position(0);
	NetworkShard* shard2 = NetworkShard::fromBinary(bshard);

	CHECK(shard->size() == shard2->size());
}
