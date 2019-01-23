/*
 * Blockchains.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "bc/CodablecashBlockchains.h"
#include "bc/BlockchainsConfig.h"
#include "bc_network/NetworkShardsStatus.h"
#include "flash/FlashBlockchain.h"
#include "main/Blockchain.h"

#include "base/StackRelease.h"
#include "base_io/File.h"

namespace codablecash {

CodablecashBlockchains::CodablecashBlockchains(const BlockchainsConfig* config) {
	this->config = new BlockchainsConfig(*config);
	this->shardStatus = nullptr;
	this->flashChain = nullptr;
	this->blockchain = nullptr;
	this->baseDir = new File(*config->baseFolder);
}

CodablecashBlockchains::~CodablecashBlockchains() {
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
	if(this->baseDir != nullptr){
		delete this->baseDir;
	}
}

void CodablecashBlockchains::init() {
	this->shardStatus = new NetworkShardsStatus(this->config->numShards);

	File* dataDir = this->baseDir->get(L"blockchain");
	StackRelease<File> __st_dataDir(dataDir);

	if(!dataDir->exists()){
		dataDir->mkdirs();
	}

	File* flashBase = dataDir->get(L"flash");
	StackRelease<File> __st_flashBase(flashBase);
	this->flashChain = new FlashBlockchain(flashBase);

    File* blockchainBase = dataDir->get(L"main");
    StackRelease<File> st_blockchainBase(blockchainBase);
    
	this->blockchain = new Blockchain(blockchainBase);

}

} /* namespace codablecash */
