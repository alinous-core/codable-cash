/*
 * DummyTrxUtils.h
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#ifndef BLOCKCHAIN_DUMMYTRXUTILS_H_
#define BLOCKCHAIN_DUMMYTRXUTILS_H_

#include <inttypes.h>

namespace codablecash {

class BlockchainAddress;
class NetworkShard;
class AbstractTransaction;

class DummyTrxUtils {
public:
	static BlockchainAddress* createAddr(const NetworkShard* shard);
	static AbstractTransaction* makeTrx(const NetworkShard* shard, uint64_t total, int numIn, int numOut, uint64_t fee);

};

} /* namespace codablecash */

#endif /* BLOCKCHAIN_DUMMYTRXUTILS_H_ */
