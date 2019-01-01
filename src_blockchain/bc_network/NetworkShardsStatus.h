/*
 * NetworkShardStatus.h
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#ifndef BC_NETWORK_NETWORKSHARDSSTATUS_H_
#define BC_NETWORK_NETWORKSHARDSSTATUS_H_

#include "filestore_block/IBlockObject.h"
#include "base/ArrayList.h"

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class NetworkShard;

class NetworkShardsStatus {
public:
	static const constexpr int MAX_SHARD_HASH{0xFF};

	explicit NetworkShardsStatus(int numShard);
	virtual ~NetworkShardsStatus();

	int size() const noexcept;
	NetworkShard* getShard(int pos) const noexcept;
private:
	int numShard;
	ArrayList<NetworkShard> shards;
};

} /* namespace codablecash */

#endif /* BC_NETWORK_NETWORKSHARDSSTATUS_H_ */
