/*
 * TransactionStore.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionStore.h"
#include "base_io/File.h"

namespace codablecash {

TransactionStore::TransactionStore(File* baseDir) {
	this->baseDir = new File(*baseDir);
}

TransactionStore::~TransactionStore() {
	delete this->baseDir;
}

} /* namespace codablecash */
