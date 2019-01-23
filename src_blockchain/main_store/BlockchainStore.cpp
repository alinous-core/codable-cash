/*
 * BlockchainStore.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "main_store/BlockchainStore.h"
#include "base_io/File.h"

namespace codablecash {

BlockchainStore::BlockchainStore(const File* baseDir) {
	this->baseDir = new File(*baseDir);

}

BlockchainStore::~BlockchainStore() {
	if(this->baseDir){
		delete this->baseDir;
	}
}

} /* namespace codablecash */
