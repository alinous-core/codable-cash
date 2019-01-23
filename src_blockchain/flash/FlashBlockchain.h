/*
 * FlashBlockchain.h
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#ifndef FLASH_FLASHBLOCKCHAIN_H_
#define FLASH_FLASHBLOCKCHAIN_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class MemPool;

class FlashBlockchain {
public:
	FlashBlockchain(const File* baseDir);
	virtual ~FlashBlockchain();

private:
	MemPool* mempool;
};

} /* namespace codablecash */

#endif /* FLASH_FLASHBLOCKCHAIN_H_ */
