/*
 * BlockchainAddress.h
 *
 *  Created on: 2018/12/30
 *      Author: iizuka
 */

#ifndef BC_BASE_BLOCKCHAINADDRESS_H_
#define BC_BASE_BLOCKCHAINADDRESS_H_

#include "bc_base/AbstractAddress.h"

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class NetworkShard;

class BlockchainAddress : public AbstractAddress {
private:
	BlockchainAddress();
public:
	virtual ~BlockchainAddress();

	static BlockchainAddress* createAddress(const NetworkShard* shard) noexcept;
	virtual AbstractAddress* clone() const noexcept;

	virtual int binarySize() const noexcept(false);
	virtual void toBinary(ByteBuffer* out) const noexcept(false);
	static BlockchainAddress* fromBinary(ByteBuffer* in) noexcept(false);

	virtual bool equals(const AbstractAddress* other) const noexcept;

	virtual IBlockObject* copyData() const noexcept;
private:
	char shardhash;
	ByteBuffer* pubkey;
	ByteBuffer* secretkey;
};

} /* namespace codablecash */

#endif /* BC_BASE_BLOCKCHAINADDRESS_H_ */
