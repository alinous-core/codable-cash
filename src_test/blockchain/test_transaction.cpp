/*
 * test_transaction.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "bc_base/Transaction.h"
#include "bc_base/BlockchainAddress.h"
#include "bc_base/BalanceUnit.h"
#include "bc_network/NetworkShard.h"

#include "base_io/ByteBuffer.h"
#include "base/StackRelease.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestTransactionGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTransactionGroup, balanceunit){
	BalanceUnit bl(111);
	CHECK(bl.getAmount() == 111)
}

TEST(TestTransactionGroup, constract){
	Transaction* trx = new Transaction();
	delete trx;
}

static BlockchainAddress* createAddr(){
	NetworkShard shard1(0, 8);
	BlockchainAddress* addr1 = BlockchainAddress::createAddress(&shard1);

	return addr1;
}

TEST(TestTransactionGroup, balancetrx){
	Transaction* trx = new Transaction();
	StackRelease<Transaction> __st_trx(trx);

	StackMultipleRelease<BlockchainAddress> release;
	BlockchainAddress* addr1 = createAddr(); release.add(addr1);
	BlockchainAddress* addr2 = createAddr(); release.add(addr2);
	BlockchainAddress* addr3 = createAddr(); release.add(addr3);
	BlockchainAddress* addr4 = createAddr(); release.add(addr4);
	BlockchainAddress* addr5 = createAddr(); release.add(addr5);

	trx->addInput(addr1, 100);
	trx->addInput(addr2, 200);
	trx->addInput(addr3, 200);

	trx->addOutput(addr4, 100);
	trx->addOutput(addr5, 399);
	trx->setFee(1);

	uint64_t in = trx->getTotalInput();
	uint64_t out = trx->getTotalOutput();
	CHECK(in == out)
}

TEST(TestTransactionGroup, binary){
	Transaction* trx = new Transaction();
	StackRelease<Transaction> __st_trx(trx);

	StackMultipleRelease<BlockchainAddress> release;
	BlockchainAddress* addr1 = createAddr(); release.add(addr1);
	BlockchainAddress* addr2 = createAddr(); release.add(addr2);
	BlockchainAddress* addr3 = createAddr(); release.add(addr3);
	BlockchainAddress* addr4 = createAddr(); release.add(addr4);
	BlockchainAddress* addr5 = createAddr(); release.add(addr5);

	trx->addInput(addr1, 100);
	trx->addInput(addr2, 200);
	trx->addInput(addr3, 200);

	trx->addOutput(addr4, 100);
	trx->addOutput(addr5, 399);
	trx->setFee(1);

	int size = trx->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true);
	trx->toBinary(buff);

	CHECK(buff->position() == size)

	buff->position(0);
	Transaction* trx2 = Transaction::fromBinary(buff);
	StackRelease<Transaction> __st_trx2(trx2);

	CHECK(buff->position() == size)
}

