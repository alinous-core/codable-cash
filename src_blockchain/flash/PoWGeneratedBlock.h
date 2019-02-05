/*
 * PoWGeneratedBlock.h
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#ifndef FLASH_POWGENERATEDBLOCK_H_
#define FLASH_POWGENERATEDBLOCK_H_

#include "flash/AbstractFlashBlock.h"

namespace codablecash {

class MinerSignature;
class Nonce;

class PoWGeneratedBlock: public AbstractFlashBlock {
private:
	friend class AbstractFlashBlock;

	PoWGeneratedBlock();

public:
	PoWGeneratedBlock(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce);
	virtual ~PoWGeneratedBlock();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

};

} /* namespace codablecash */

#endif /* FLASH_POWGENERATEDBLOCK_H_ */
