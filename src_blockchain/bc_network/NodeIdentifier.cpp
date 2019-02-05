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

NodeIdentifier::NodeIdentifier(const NodeIdentifier& inst) {
	this->pair = inst.pair->clone();
	this->shard = new NetworkShard(*inst.shard);
}

int NodeIdentifier::binarySize() const {
	return this->pair->binarySize() + this->shard->binarySize();
}

void NodeIdentifier::toBinary(ByteBuffer* out) const {
	this->pair->toBinary(out);
	this->shard->toBinary(out);
}

NodeIdentifier* NodeIdentifier::fromBinary(ByteBuffer* in) {
	NodeIdentifier* nodeId = new NodeIdentifier();

	nodeId->pair = IKeyPair::createFromBinary(in);
	nodeId->shard = NetworkShard::fromBinary(in);

	return nodeId;
}

NodeIdentifier NodeIdentifier::create(const NetworkShard* shard) {
	NodeIdentifier nodeId;
	nodeId.pair = Schnorr::generateKey();
	nodeId.shard = new NetworkShard(*shard);

	return std::move(nodeId);
}

} /* namespace codablecash */
