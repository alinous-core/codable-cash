/*
 * BTreeOnMemory.h
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_BTREEONMEMORY_H_
#define BTREE_MEMORY_BTREEONMEMORY_H_

namespace alinous {

class BtreeKeyFactory;
class AbstractBtreeDataFactory;

class BTreeOnMemory {
public:
	BTreeOnMemory(BtreeKeyFactory* factory, AbstractBtreeDataFactory* dfactory);
	virtual ~BTreeOnMemory();

private:
	BtreeKeyFactory* factory;
	AbstractBtreeDataFactory* dfactory;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_BTREEONMEMORY_H_ */
