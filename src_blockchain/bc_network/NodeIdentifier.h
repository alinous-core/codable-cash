/*
 * NodeIdentifier.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef BC_NETWORK_NODEIDENTIFIER_H_
#define BC_NETWORK_NODEIDENTIFIER_H_
#include "filestore_block/IBlockObject.h"

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class IKeyPair;

class NetworkShard;

class NodeIdentifier : public IBlockObject {
public:
	NodeIdentifier& operator= (NodeIdentifier&& inst);
	NodeIdentifier(NodeIdentifier&& inst);
	NodeIdentifier(const NodeIdentifier& inst);

	NodeIdentifier();
	virtual ~NodeIdentifier();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;

	static NodeIdentifier create(const NetworkShard* shard);

private:
	NetworkShard* shard;
	IKeyPair* pair;

};

} /* namespace codablecash */

#endif /* BC_NETWORK_NODEIDENTIFIER_H_ */
