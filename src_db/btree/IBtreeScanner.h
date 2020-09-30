/*
 * IBtreeScanner.h
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#ifndef BTREE_IBTREESCANNER_H_
#define BTREE_IBTREESCANNER_H_

namespace alinous {
class AbstractBtreeKey;
class IBlockObject;
}
using namespace alinous;

namespace alinous {

class IBtreeScanner {
public:
	IBtreeScanner();
	virtual ~IBtreeScanner();

	virtual void begin() = 0;
	virtual void begin(const AbstractBtreeKey* key) = 0;
	virtual bool hasNext() = 0;

	virtual const IBlockObject* next() = 0;
	virtual const AbstractBtreeKey* nextKey() = 0;
};

} /* namespace alinous */

#endif /* BTREE_IBTREESCANNER_H_ */
