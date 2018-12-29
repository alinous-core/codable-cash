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

class BtreeScanner {
public:
	BtreeScanner(NodeCursor* cursor);
	virtual ~BtreeScanner();

private:
	NodeCursor* cursor;
};

} /* namespace alinous */

#endif /* BTREE_BTREESCANNER_H_ */
