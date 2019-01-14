/*
 * DummyTrxUtils.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "blockchain/DummyTrxUtils.h"
#include "base/StackRelease.h"

#include "bc_base/Transaction.h"
#include "bc_base/BlockchainAddress.h"
#include "bc_base/BalanceUnit.h"
#include "bc_network/NetworkShard.h"
#include "bc_network/NetworkShardsStatus.h"

namespace codablecash {

BlockchainAddress* DummyTrxUtils::createAddr(const NetworkShard* shard) {
	BlockchainAddress* addr1 = BlockchainAddress::createAddress(shard);
	return addr1;
}

AbstractTransaction* DummyTrxUtils::makeTrx(const NetworkShard* shard, uint64_t total, int numIn, int numOut, uint64_t fee) {
	Transaction* trx = new Transaction();

	int maxLoop = numIn - 1;
	uint64_t remain = total;
	uint64_t one = total / numIn;
	for(int i = 0; i != maxLoop; ++i){
		BlockchainAddress* addr = createAddr(shard);
		StackRelease<BlockchainAddress> __st_addr(addr);

		trx->addInput(addr, one);

		remain -= one;
	}
	{
		BlockchainAddress* addr = createAddr(shard);
		StackRelease<BlockchainAddress> __st_addr(addr);
		trx->addInput(addr, remain);
	}

	maxLoop = numOut;
	remain = total;
	one = (total - fee) / numOut;
	for(int i = 0; i != maxLoop; ++i){
		BlockchainAddress* addr = createAddr(shard);
		StackRelease<BlockchainAddress> __st_addr(addr);

		trx->addOutput(addr, one);
		remain -= one;
	}

	trx->setFee(remain);

	return trx;
}

} /* namespace codablecash */


