/*
 * NodeHandle.cpp
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#include "btree/NodeHandle.h"
#include "btree/NodeCacheRef.h"

namespace alinous {

NodeHandle::NodeHandle(NodeCacheRef* ref) {
	this->ref = ref;
	ref->inc();
}

NodeHandle::~NodeHandle() {
	ref->dec();
}

} /* namespace alinous */
