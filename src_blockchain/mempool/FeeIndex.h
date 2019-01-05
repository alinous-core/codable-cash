/*
 * FeeIndex.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_FEEINDEX_H_
#define MEMPOOL_FEEINDEX_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class FeeIndex {
public:
	FeeIndex(File* baseDir);
	virtual ~FeeIndex();

private:
	File* baseDir;
};

} /* namespace codablecash */

#endif /* MEMPOOL_FEEINDEX_H_ */
