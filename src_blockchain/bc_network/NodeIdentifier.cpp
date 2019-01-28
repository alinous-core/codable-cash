/*
 * NodeIdentifier.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "NodeIdentifier.h"

#include <algorithm>
#include "crypto/Schnorr.h"
#include "crypto/IKeyPair.h"
#include "NetworkShard.h"


namespace codablecash {

NodeIdentifier::NodeIdentifier() {
	this->pair = nullptr;
	this->shard = nullptr;
}

NodeIdentifier::~NodeIdentifier() {
	delete this->pair;
	delete this->shard;
}

NodeIdentifier& NodeIdentifier::operator =(NodeIdentifier&& inst) {
	if(this != &inst){
		this->pair = inst.pair;
		this->shard = inst.shard;

		inst.pair = nullptr;
		inst.shard = nullptr;
	}
	return *this;
}

NodeIdentifier::NodeIdentifier(NodeIdentifier&& inst) {
	this->pair = inst.pair;
	this->shard = inst.shard;

	inst.pair = nullptr;
	inst.shard = nullptr;
}

NodeIdentifier NodeIdentifier::create(const NetworkShard* shard) {
	NodeIdentifier nodeId;
	nodeId.pair = Schnorr::generateKey();
	nodeId.shard = new NetworkShard(*shard);

	return std::move(nodeId);
}

} /* namespace codablecash */
