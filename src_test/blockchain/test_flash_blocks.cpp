/*
 * test_flash_transactions.cpp
 *
 *  Created on: 2019/01/27
 *      Author: iizuka
 */

#include "bc_network/NetworkShardsStatus.h"
#include "flash/PoWGeneratedBlock.h"
#include "test_utils/t_macros.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestFlashBlocks) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestFlashBlocks, newPow){
	NetworkShardsStatus* address = new NetworkShardsStatus(8); __STP(address);

	//MinerSignature sig();

	//PoWGeneratedBlock* block = new PoWGeneratedBlock();

}


