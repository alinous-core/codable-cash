/*
 * NetworkShard.h
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#ifndef BC_NETWORK_NETWORKSHARD_H_
#define BC_NETWORK_NETWORKSHARD_H_

#include "filestore_block/IBlockObject.h"
#include <cstdlib>

namespace codablecash {
using namespace alinous;

class NetworkShard : public IBlockObject {
private:
	NetworkShard();
public:
	NetworkShard(const NetworkShard& inst) = default;
	NetworkShard(int start, int length);
	virtual ~NetworkShard();

	int size() const noexcept;

	char getRandomHash() const noexcept;
	NetworkShard* clone() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static NetworkShard* fromBinary(ByteBuffer* in);

	virtual IBlockObject* copyData() const noexcept;

private:
	int32_t begin;
	int32_t end;
};

} /* namespace codablecash */

#endif /* BC_NETWORK_NETWORKSHARD_H_ */
