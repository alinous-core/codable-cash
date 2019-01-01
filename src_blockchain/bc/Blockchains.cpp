/*
 * Blockchains.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "bc/Blockchains.h"
#include "bc/BlockchainsConfig.h"
#include "bc_network/NetworkShardsStatus.h"
#include "flash/FlashBlockchain.h"
#include "main/Blockchain.h"

namespace codablecash {

Blockchains::Blockchains(const BlockchainsConfig* config) {
	this->config = new BlockchainsConfig(*config);
	this->shardStatus = nullptr;
	this->flashChain = nullptr;
	this->blockchain = nullptr;
}

Blockchains::~Blockchains() {
	delete this->config;
	if(this->shardStatus != nullptr){
		delete this->shardStatus;
	}
	if(this->flashChain != nullptr){
		delete this->flashChain;
	}
	if(this->blockchain != nullptr){
		delete this->blockchain;
	}
}

void Blockchains::init() {
	this->shardStatus = new NetworkShardsStatus(this->config->numShards);

	this->flashChain = new FlashBlockchain();
	this->blockchain = new Blockchain();

}

} /* namespace codablecash */
