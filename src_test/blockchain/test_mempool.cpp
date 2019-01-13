/*
 * test_mempool.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "mempool/MemPool.h"

#include "base_io/ByteBuffer.h"
#include "base/StackRelease.h"

#include "bc_base/Transaction.h"
#include "bc_base/BlockchainAddress.h"
#include "bc_base/BalanceUnit.h"
#include "bc_network/NetworkShard.h"
#include "bc_network/NetworkShardsStatus.h"

#include "blockchain/DummyTrxUtils.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestMempoolGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestMempoolGroup, constract){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))

	MemPool memPool(baseDir);
}

TEST(TestMempoolGroup, init){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))

	{
		MemPool memPool(baseDir, 2048);
		memPool.init();
		memPool.close();
	}

	{
		MemPool memPool(baseDir);
		memPool.init();
		memPool.close();
	}
}

TEST(TestMempoolGroup, addTrx){
	File projectFolder = this->env->testCaseDir();
	_ST(File, baseDir, projectFolder.get(L"store"))

	NetworkShardsStatus* address = new NetworkShardsStatus(8);
	StackRelease<NetworkShardsStatus> __st_address(address);
	NetworkShard* shard = address->getShard(2);

	MemPool memPool(baseDir);
	memPool.init();

	{
		AbstractTransaction* trx = DummyTrxUtils::makeTrx(shard, 1000, 2, 3, 1);
		StackRelease<AbstractTransaction> __st_trx(trx);

		memPool.addTransaction(trx);
	}


	memPool.close();

}
