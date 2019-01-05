/*
 * FeeIndex.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/FeeIndex.h"
#include "base_io/File.h"

namespace codablecash {

FeeIndex::FeeIndex(File* baseDir) {
	this->baseDir = new File(*baseDir);

}

FeeIndex::~FeeIndex() {
	delete this->baseDir;
}

} /* namespace codablecash */
