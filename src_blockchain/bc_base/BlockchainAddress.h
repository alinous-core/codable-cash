/*
 * BlockchainAddress.h
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#ifndef BC_BASE_BLOCKCHAINADDRESS_H_
#define BC_BASE_BLOCKCHAINADDRESS_H_

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class NetworkShard;

class BlockchainAddress {
private:
	BlockchainAddress();
public:

	virtual ~BlockchainAddress();

	static BlockchainAddress* createAddress(NetworkShard* shard) noexcept;

private:
	char shardhash;
	ByteBuffer* pubkey;
	ByteBuffer* secretkey;
};

} /* namespace codablecash */

#endif /* BC_BASE_BLOCKCHAINADDRESS_H_ */
