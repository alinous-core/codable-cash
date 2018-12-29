/*
 * NodePosition.h
 *
 *  Created on: 2018/12/29
 *      Author: iizuka
 */

#ifndef BTREE_NODEPOSITION_H_
#define BTREE_NODEPOSITION_H_

#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

#include <inttypes.h>

namespace alinous {

class NodeHandle;
class AbstractBtreeKey;
class BtreeStorage;

class NodePosition {
public:
	explicit NodePosition(NodeHandle* nodeHandle);
	~NodePosition();

	bool isLeaf() const;
	bool isRoot() const;
	void setRoot(bool isroot);
	NodeHandle* hasKey(const AbstractBtreeKey* key) const;
	bool isFull(int nodeNumber) const noexcept;

	ArrayList<NodeHandle>* getInnerNodes() const noexcept;

	void loadInnerNodes(BtreeStorage* store);

	void addNode(const AbstractBtreeKey* key, uint64_t fpos, int nodeNumber);
	void save(BtreeStorage* store);

	static void checkNoNull(NodeHandle* nodeHandle, const char* srcfile, int srcline) noexcept(false);
private:
	void internalAddNode(int index, uint64_t fpos);

private:
	int pos;
	NodeHandle* node;
	ArrayList<NodeHandle>* innerNodes;
	int innerCount;
};

} /* namespace alinous */

#endif /* BTREE_NODEPOSITION_H_ */
