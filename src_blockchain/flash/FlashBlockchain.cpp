/*
 * FlashBlockchain.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "flash/FlashBlockchain.h"
#include "mempool/MemPool.h"

#include "base_io/File.h"

namespace codablecash {

FlashBlockchain::FlashBlockchain(const File* baseDir) {
	this->mempool = nullptr;
}

FlashBlockchain::~FlashBlockchain() {
	if(this->mempool){
		delete mempool;
	}
}

} /* namespace codablecash */
