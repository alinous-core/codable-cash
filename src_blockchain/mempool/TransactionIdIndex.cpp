/*
 * TransactionIdIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionIdIndex.h"
#include "base_io/File.h"

namespace codablecash {

TransactionIdIndex::TransactionIdIndex(File* baseDir) {
	this->baseDir = new File(*baseDir);
}

TransactionIdIndex::~TransactionIdIndex() {
	delete this->baseDir;
}

} /* namespace codablecash */
