/*
 * test_flash_transactions.cpp
 *
 *  Created on: 2019/01/27
 *      Author: iizuka
 */

#include "flash_pow/Nonce.h"
#include "flash/MinerSignature.h"
#include "bc_network/NodeIdentifier.h"
#include "bc_network/NetworkShardsStatus.h"
#include "flash/PoWGeneratedBlock.h"
#include "test_utils/t_macros.h"
#include "base_io/ByteBuffer.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestFlashBlocks) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestFlashBlocks, newPow){
	NetworkShardsStatus* address = new NetworkShardsStatus(8); __STP(address);

	NodeIdentifier nodeId = NodeIdentifier::create(address->getShard(2));
	MinerSignature sig(&nodeId);
	Nonce nonce(1, 2);

	PoWGeneratedBlock* block = new PoWGeneratedBlock(1, &sig, &nonce); __STP(block);

	int cap = block->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(cap, true);
	block->toBinary(buff);



}


