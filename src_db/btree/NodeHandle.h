/*
 * NodeHandle.h
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#ifndef BTREE_NODEHANDLE_H_
#define BTREE_NODEHANDLE_H_

namespace alinous {

class NodeCacheRef;

class NodeHandle {
public:
	NodeHandle(const NodeHandle& inst) = delete;
	explicit NodeHandle(NodeCacheRef* ref);
	virtual ~NodeHandle();

private:
	NodeCacheRef* ref;
};

} /* namespace alinous */

#endif /* BTREE_NODEHANDLE_H_ */
