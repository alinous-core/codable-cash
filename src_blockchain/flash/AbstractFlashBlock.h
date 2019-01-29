/*
 * AbstractFlashBlock.h
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#ifndef FLASH_ABSTRACTFLASHBLOCK_H_
#define FLASH_ABSTRACTFLASHBLOCK_H_
#include <cstdint>

#include "filestore_block/IBlockObject.h"
#include "base/ArrayList.h"

namespace codablecash {
using namespace alinous;

class AbstractTransaction;

class MinerSignature;
class AbstractFlashBlockHeader;

class AbstractFlashBlock : public IBlockObject {
public:
	static const constexpr uint8_t BLK_TICKET{0x01};
	static const constexpr uint8_t BLK_POW{0x02};

	explicit AbstractFlashBlock(uint8_t type);
	virtual ~AbstractFlashBlock();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
protected:
	uint8_t type;
	AbstractFlashBlockHeader* header;
	ArrayList<AbstractTransaction> list;
};

} /* namespace codablecash */

#endif /* FLASH_ABSTRACTFLASHBLOCK_H_ */
