/*
 * test_address.cpp
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "bc_base/BlockchainAddress.h"
#include "bc_network/NetworkShardsStatus.h"

#include "base/StackRelease.h"

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



