/*
 * FlashChainStore.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash_store/FlashChainStore.h"
#include "base_io/File.h"

namespace codablecash {

FlashChainStore::FlashChainStore(const File* baseDir) {
	this->baseDir = new File(*baseDir);

}

FlashChainStore::~FlashChainStore() {
	delete this->baseDir;
}

} /* namespace codablecash */
