/*
 * FlashBlockchain.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "flash/FlashBlockchain.h"
#include "mempool/MemPool.h"
#include "flash_store/FlashChainStore.h"

#include "base_io/File.h"

namespace codablecash {

FlashBlockchain::FlashBlockchain(const File* baseDir) {
	this->mempool = new MemPool(baseDir);
	this->store = new FlashChainStore(baseDir);
}

FlashBlockchain::~FlashBlockchain() {
	if(this->mempool){
		delete mempool;
	}
	if(this->store){
		delete this->store;
	}
}

} /* namespace codablecash */
