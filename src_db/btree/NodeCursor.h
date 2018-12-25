/*
 * NodeCursor.h
 *
 *  Created on: 2018/12/26
 *      Author: iizuka
 */

#ifndef BTREE_NODECURSOR_H_
#define BTREE_NODECURSOR_H_



namespace alinous {

class NodeHandle;

class NodeCursor {
public:
	explicit NodeCursor(NodeHandle* rootNode);
	virtual ~NodeCursor();

private:

};

} /* namespace alinous */

#endif /* BTREE_NODECURSOR_H_ */
