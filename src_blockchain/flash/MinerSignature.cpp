/*
 * MinerSignature.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "MinerSignature.h"

#include "bc_network/NodeIdentifier.h"

namespace codablecash {

MinerSignature::MinerSignature(const MinerSignature& inst) {
	this->nodeId = new NodeIdentifier(*inst.nodeId);
}

MinerSignature::MinerSignature(const NodeIdentifier* nodeId) {
	this->nodeId = new NodeIdentifier(*nodeId);
}

MinerSignature::~MinerSignature() {
	delete this->nodeId;
}

int MinerSignature::binarySize() const {
	// FIXME MinerSignature
}

void MinerSignature::toBinary(ByteBuffer* out) const {

}

} /* namespace codablecash */
