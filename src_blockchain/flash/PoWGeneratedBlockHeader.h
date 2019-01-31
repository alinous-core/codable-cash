/*
 * PoWGeneratedBlockHeader.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_POWGENERATEDBLOCKHEADER_H_
#define FLASH_POWGENERATEDBLOCKHEADER_H_

#include "AbstractFlashBlockHeader.h"

namespace codablecash {

class Nonce;
class MinerSignature;

class PoWGeneratedBlockHeader : public AbstractFlashBlockHeader {
private:
	friend class AbstractFlashBlockHeader;
	PoWGeneratedBlockHeader();
public:
	PoWGeneratedBlockHeader(uint64_t height, const MinerSignature* minerSig, const Nonce* nonce);
	virtual ~PoWGeneratedBlockHeader();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);
private:

};

} /* namespace codablecash */

#endif /* FLASH_POWGENERATEDBLOCKHEADER_H_ */
