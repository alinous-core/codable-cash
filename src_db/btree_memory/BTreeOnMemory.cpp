/*
 * BTreeOnMemory.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/BTreeOnMemory.h"

#include "btreekey/BtreeKeyFactory.h"

#include "btree/AbstractBtreeDataFactory.h"

namespace alinous {

BTreeOnMemory::BTreeOnMemory(BtreeKeyFactory* factory, AbstractBtreeDataFactory* dfactory) {
	this->factory = factory;
	this->dfactory = dfactory;
}

BTreeOnMemory::~BTreeOnMemory() {
	delete this->factory;
	delete this->dfactory;
}

} /* namespace alinous */
