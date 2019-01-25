/*
 * NodeIdentifier.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "NodeIdentifier.h"

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

} /* namespace codablecash */
