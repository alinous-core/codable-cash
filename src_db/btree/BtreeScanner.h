/*
 * BtreeScanner.h
 *
 *  Created on: 2018/12/29
 *      Author: iizuka
 */

#ifndef BTREE_BTREESCANNER_H_
#define BTREE_BTREESCANNER_H_

#include "btree/IBtreeScanner.h"

namespace alinous {

class NodeCursor;
class NodeHandle;
class IBlockObject;
class AbstractBtreeKey;

class BtreeScanner : public IBtreeScanner {
public:
	BtreeScanner(const BtreeScanner& inst) = delete;
	explicit BtreeScanner(NodeCursor* cursor);
	virtual ~BtreeScanner();

	virtual void begin();
	virtual void begin(const AbstractBtreeKey* key);
	virtual bool hasNext();

	virtual const IBlockObject* next();
	virtual const AbstractBtreeKey* nextKey();

private:
	NodeCursor* cursor;
	IBlockObject* nextObj;
	bool initialized;
	AbstractBtreeKey* key;
};

} /* namespace alinous */

#endif /* BTREE_BTREESCANNER_H_ */
