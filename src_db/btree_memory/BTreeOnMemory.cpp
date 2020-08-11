/*
 * BTreeOnMemory.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/BTreeOnMemory.h"

#include "btreekey/BtreeKeyFactory.h"

#include "btree/AbstractBtreeDataFactory.h"
#include "btree/BtreeConfig.h"

namespace alinous {

BTreeOnMemory::BTreeOnMemory(BtreeConfig* config, BtreeKeyFactory* factory, AbstractBtreeDataFactory* dfactory) {
	this->config = config;
	this->factory = factory;
	this->dfactory = dfactory;
}

BTreeOnMemory::~BTreeOnMemory() {
	delete this->config;
	delete this->factory;
	delete this->dfactory;
}

} /* namespace alinous */
