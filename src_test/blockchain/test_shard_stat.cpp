/*
 * test_shard_stat.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "bc_network/NetworkShardsStatus.h"
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


