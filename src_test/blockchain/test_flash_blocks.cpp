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
#include "flash/TicketGeneratedBlock.h"
#include "flash/AbstractFlashBlockHeader.h"
#include "test_utils/t_macros.h"
#include "base_io/ByteBuffer.h"

#include "DummyTrxUtils.h"
#include "bc_base/AbstractTransaction.h"

#include "base/Exception.h"


using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestFlashBlocks) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestFlashBlocks, blockCreationError){
	Exception* ex = nullptr;

	try{
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(32, true); __STP(buff);
		buff->putShort(12345);
		buff->position(0);

		AbstractFlashBlock::createFromBinary(buff);
	}
	catch (Exception* e) {
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestFlashBlocks, blockHeaderCreationError){
	Exception* ex = nullptr;

	try{
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(32, true); __STP(buff);
		buff->putShort(12345);
		buff->position(0);

		AbstractFlashBlockHeader::createFromBinary(buff);
	}
	catch (Exception* e) {
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
}


TEST(TestFlashBlocks, newPow){
	NetworkShardsStatus* address = new NetworkShardsStatus(8); __STP(address);

	NodeIdentifier nodeId = NodeIdentifier::create(address->getShard(2));
	MinerSignature sig(&nodeId);
	Nonce nonce(1, 2);

	PoWGeneratedBlock* block = new PoWGeneratedBlock(1, &sig, &nonce); __STP(block);

	int cap = block->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(cap, true); __STP(buff);
	block->toBinary(buff);

	CHECK(buff->position() == cap)

	buff->position(0);
	AbstractFlashBlock* resBlock = AbstractFlashBlock::createFromBinary(buff); __STP(resBlock);

	CHECK(buff->position() == cap)
}

TEST(TestFlashBlocks, newTicket){
	NetworkShardsStatus* address = new NetworkShardsStatus(8); __STP(address);

	NodeIdentifier nodeId = NodeIdentifier::create(address->getShard(2));
	MinerSignature sig(&nodeId);
	Nonce nonce(1, 2);

	AbstractFlashBlock* block = new TicketGeneratedBlock(1, &sig, &nonce); __STP(block);

	AbstractTransaction* trx = DummyTrxUtils::makeTrx(address->getShard(2), 100, 2, 2, 1);
	block->addTrx(trx);

	int cap = block->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(cap, true); __STP(buff);
	block->toBinary(buff);

	CHECK(buff->position() == cap)

	buff->position(0);
	AbstractFlashBlock* resBlock = AbstractFlashBlock::createFromBinary(buff); __STP(resBlock);

	CHECK(buff->position() == cap)
}



