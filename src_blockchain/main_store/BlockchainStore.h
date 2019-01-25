/*
 * BlockchainStore.h
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#ifndef MAIN_STORE_BLOCKCHAINSTORE_H_
#define MAIN_STORE_BLOCKCHAINSTORE_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class BlockchainStore {
public:
	BlockchainStore(const File* baseDir);
	virtual ~BlockchainStore();

private:
	File* baseDir;
};

} /* namespace codablecash */

#endif /* MAIN_STORE_BLOCKCHAINSTORE_H_ */
