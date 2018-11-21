/*
 * BlockData.cpp
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#include "filestore_block/BlockData.h"

namespace alinous {

BlockData::BlockData(uint16_t blockSize, uint64_t currentPos) noexcept {
	this->blockSize = blockSize;
	this->currentPos = currentPos;

	this->used = 0;
	this->nextPos = 0;
}

BlockData::~BlockData() {

}

} /* namespace alinous */
