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

class BtreeScanner {
public:
	BtreeScanner(const BtreeScanner& inst) = delete;
	explicit BtreeScanner(NodeCursor* cursor);
	virtual ~BtreeScanner();

	void begin();
	bool hasNext();
	NodeHandle* next();

private:
	NodeCursor* cursor;
};

} /* namespace alinous */

#endif /* BTREE_BTREESCANNER_H_ */
