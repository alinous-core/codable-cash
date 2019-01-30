/*
 * AbstractFlashBlockHeader.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_ABSTRACTFLASHBLOCKHEADER_H_
#define FLASH_ABSTRACTFLASHBLOCKHEADER_H_

#include <cstdint>

#include "filestore_block/IBlockObject.h"

namespace codablecash {
using namespace alinous;

class MinerSignature;
class Nonce;

class AbstractFlashBlockHeader : public IBlockObject {
private:
	AbstractFlashBlockHeader(int kind);
public:
	static const constexpr uint8_t BLKH_TICKET_V0{0x01};
	static const constexpr uint8_t BLKH_POW_V0{0x02};

	AbstractFlashBlockHeader(int kind, uint64_t height, const MinerSignature* minerSig, const Nonce* nonce);
	virtual ~AbstractFlashBlockHeader();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static AbstractFlashBlockHeader* fromBinary(ByteBuffer* in);

protected:
	uint8_t kind;
	uint64_t height;
	MinerSignature* minerSig;
	Nonce* nonce;
};

} /* namespace codablecash */

#endif /* FLASH_ABSTRACTFLASHBLOCKHEADER_H_ */
