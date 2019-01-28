/*
 * MinerSignature.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "MinerSignature.h"
#include "bc_network/NodeIdentifier.h"

namespace codablecash {

MinerSignature::MinerSignature(NodeIdentifier* nodeId) {
	this->nodeId = nodeId;
}

MinerSignature::~MinerSignature() {
	delete this->nodeId;
}

} /* namespace codablecash */
