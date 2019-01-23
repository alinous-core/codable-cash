/*
 * Blockchain.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "main/Blockchain.h"
#include "base_io/File.h"

#include "main_store/BlockchainStore.h"


namespace codablecash {

Blockchain::Blockchain(const File* baseDir) {
	this->baseDir = new File(*baseDir);
	this->store = new BlockchainStore(baseDir);
}

Blockchain::~Blockchain() {
	if(this->baseDir){
		delete this->baseDir;
	}
	if(this->store){
		delete this->store;
	}
}

} /* namespace codablecash */
