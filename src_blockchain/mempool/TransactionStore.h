/*
 * TransactionStore.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONSTORE_H_
#define MEMPOOL_TRANSACTIONSTORE_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class TransactionStore {
public:
	TransactionStore(File* baseDir);
	virtual ~TransactionStore();

private:
	File* baseDir;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONSTORE_H_ */
