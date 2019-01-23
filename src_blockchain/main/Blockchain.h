/*
 * Blockchain.h
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#ifndef MAIN_BLOCKCHAIN_H_
#define MAIN_BLOCKCHAIN_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class BlockchainStore;

class Blockchain {
public:
	Blockchain(const File* baseDir);
	virtual ~Blockchain();

private:
	File* baseDir;
	BlockchainStore* store;
};

} /* namespace codablecash */

#endif /* MAIN_BLOCKCHAIN_H_ */
