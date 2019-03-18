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
#include "bc/exceptions.h"

#include "bc_base/TicketTransaction.h"

#include "flash_pow/Nonce.h"

#include "bc_base/TransactionId.h"
using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestTransactionGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTransactionGroup, balanceunit){
	BalanceUnit bl(111);
	CHECK(bl.getAmount() == 111)

	BalanceUnit bl2(bl);
	CHECK(bl2.getAmount() == 111)
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

TEST(TestTransactionGroup, testMulformatException){
	testException<MulformattedTransactionBinaryException>();
}

TEST(TestTransactionGroup, factoryerror){
	ByteBuffer* in = ByteBuffer::allocateWithEndian(4, true);
	StackRelease<ByteBuffer> __st_buff(in);
	in->put(-1);

	Exception* ex = nullptr;
	try{
		AbstractTransaction* trx = AbstractTransaction::fromBinary(in);
	}
	catch(Exception* e){
		ex = e;
	}

	CHECK(ex != nullptr)
	delete ex;
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
	trx->setFee(BalanceUnit(1));

	uint64_t in = trx->getTotalInput();
	uint64_t out = trx->getTotalOutput();
	CHECK(in == out)
}

TEST(TestTransactionGroup, trxid){
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
	trx->setFee(BalanceUnit(1));

	trx->updateTransactionId();
	trx->updateTransactionId();

	const TransactionId* trxId = trx->getTransactionId();
	CHECK(trxId != nullptr)
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
	trx->setFee(BalanceUnit(1));

	int size = trx->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true);
	StackRelease<ByteBuffer> __st_buff(buff);
	trx->toBinary(buff);

	CHECK(buff->position() == size)

	buff->position(0);
	Transaction* trx2 = dynamic_cast<Transaction*>(AbstractTransaction::fromBinary(buff));
	StackRelease<Transaction> __st_trx2(trx2);

	CHECK(buff->position() == size)

	// check binary
	size = trx2->binarySize();
	ByteBuffer* buff2 = ByteBuffer::allocateWithEndian(size, true);
	StackRelease<ByteBuffer> __st_buff2(buff2);
	trx2->toBinary(buff2);

	CHECK(buff2->capacity() == buff->capacity())
	CHECK(Mem::memcmp(buff->array(), buff2->array(), buff->capacity()) == 0)
}

TEST(TestTransactionGroup, copy){
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
	trx->setFee(BalanceUnit(1));

	trx->updateTransactionId();

	int size = trx->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true);
	StackRelease<ByteBuffer> __st_buff(buff);
	trx->toBinary(buff);

	CHECK(buff->position() == size)

	buff->position(0);
	Transaction* trx2 = new Transaction(*trx);
	StackRelease<Transaction> __st_trx2(trx2);

	// check binary
	size = trx2->binarySize();
	ByteBuffer* buff2 = ByteBuffer::allocateWithEndian(size, true);
	StackRelease<ByteBuffer> __st_buff2(buff2);
	trx2->toBinary(buff2);

	CHECK(buff2->capacity() == buff->capacity())
	CHECK(Mem::memcmp(buff->array(), buff2->array(), buff->capacity()) == 0)
}

TEST(TestTransactionGroup, constractTicketTrx){
	TicketTransaction trx(1L);
}

TEST(TestTransactionGroup, ticketTrxTransactionId){
	TicketTransaction trx(1L);
	Nonce nonce(1, 2);
	BalanceUnit fee(10L);

	trx.setNonce(&nonce);
	trx.setFee(&fee);

	trx.updateTransactionId();

	trx.updateTransactionId();
}

TEST(TestTransactionGroup, ticketTrxClone){
	TicketTransaction trx(1L);
	Nonce nonce(1, 2);
	BalanceUnit fee(10L);

	trx.setNonce(&nonce);
	trx.setFee(&fee);
	trx.updateTransactionId();

	TicketTransaction* trx2 = dynamic_cast<TicketTransaction*>(trx.clone()); __STP(trx2);
	CHECK(fee.getAmount() == trx2->getFee()->getAmount())

	trx2->updateTransactionId();

	const TransactionId* id1 = trx.getTransactionId();
	const TransactionId* id2 = trx2->getTransactionId();

	CHECK(id1->equals(id2))
}
