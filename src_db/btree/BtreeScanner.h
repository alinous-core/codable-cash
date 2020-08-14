/*
 * BtreeScanner.h
 *
 *  Created on: 2018/12/29
 *      Author: iizuka
 */

#ifndef BTREE_BTREESCANNER_H_
#define BTREE_BTREESCANNER_H_

namespace alinous {

class NodeCursor;
class NodeHandle;
class IBlockObject;
class AbstractBtreeKey;

class BtreeScanner {
public:
	BtreeScanner(const BtreeScanner& inst) = delete;
	explicit BtreeScanner(NodeCursor* cursor);
	virtual ~BtreeScanner();

	void begin();
	void begin(const AbstractBtreeKey* key);
	bool hasNext();

	const IBlockObject* next();
	const AbstractBtreeKey* nextKey();
private:
	NodeCursor* cursor;
	IBlockObject* nextObj;
	bool initialized;
	AbstractBtreeKey* key;
};

} /* namespace alinous */

#endif /* BTREE_BTREESCANNER_H_ */
