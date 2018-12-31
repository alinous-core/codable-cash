/*
 * test_shard_stat.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "bc_network/NetworkShardStatus.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestShardStatGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestShardStatGroup, constract){
	NetworkShardStatus* address = new NetworkShardStatus();
	delete address;
}


