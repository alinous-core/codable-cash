/*
 * AbstractFlashBlock.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash/AbstractFlashBlock.h"

#include "AbstractFlashBlockHeader.h"
#include "bc_base/AbstractTransaction.h"
#include "MinerSignature.h"
#include "base_io/ByteBuffer.h"

#include "flash/PoWGeneratedBlock.h"

namespace codablecash {

AbstractFlashBlock::AbstractFlashBlock(uint16_t type) {
	this->type = type;
	this->header = nullptr;
}

AbstractFlashBlock::~AbstractFlashBlock() {
	this->list.deleteElements();
}

int AbstractFlashBlock::binarySize() const {
	int total = sizeof(this->type);
	total += this->header->binarySize();

	total += sizeof(int32_t);
	int maxloop = this->list.size();
	for(int i = 0; i != maxloop; ++i){
		AbstractTransaction* trx = this->list.get(i);
		total += trx->binarySize();
	}

	return total;
}

void AbstractFlashBlock::toBinary(ByteBuffer* out) const {
	out->putShort(this->type);
	this->header->toBinary(out);

	int maxloop = this->list.size();
	out->putInt(maxloop);

	for(int i = 0; i != maxloop; ++i){
		AbstractTransaction* trx = this->list.get(i);
		trx->toBinary(out);
	}
}

void AbstractFlashBlock::fromBinary(ByteBuffer* in) {
	//this->header =
}

AbstractFlashBlock* AbstractFlashBlock::createFromBinary(ByteBuffer* in) {
	uint16_t type = in->getShort();

	AbstractFlashBlock* blk = nullptr;
	switch (type) {
		case AbstractFlashBlock::BLK_POW_V0:
			blk = new PoWGeneratedBlock();
			break;
		case AbstractFlashBlock::BLK_TICKET_V0:

			break;
		default:
			break;
	}

	blk->fromBinary(in);
	return blk;
}

} /* namespace codablecash */
