/*
 * FlashChainStore.h
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#ifndef FLASH_STORE_FLASHCHAINSTORE_H_
#define FLASH_STORE_FLASHCHAINSTORE_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class FlashChainStore {
public:
	FlashChainStore(const File* baseDir);
	virtual ~FlashChainStore();
};

} /* namespace codablecash */

#endif /* FLASH_STORE_FLASHCHAINSTORE_H_ */
