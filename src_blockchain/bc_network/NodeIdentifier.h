/*
 * NodeIdentifier.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef BC_NETWORK_NODEIDENTIFIER_H_
#define BC_NETWORK_NODEIDENTIFIER_H_

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class IKeyPair;

class NetworkShard;

class NodeIdentifier {
public:
	NodeIdentifier& operator= (NodeIdentifier&& inst);
	NodeIdentifier(NodeIdentifier&& inst);

	NodeIdentifier();
	virtual ~NodeIdentifier();



	static NodeIdentifier create(const NetworkShard* shard);

private:
	NetworkShard* shard;
	IKeyPair* pair;

};

} /* namespace codablecash */

#endif /* BC_NETWORK_NODEIDENTIFIER_H_ */
