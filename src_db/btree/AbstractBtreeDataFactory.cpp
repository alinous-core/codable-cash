/*
 * AbstractBtreeDataFactory.cpp
 *
 *  Created on: 2018/12/27
 *      Author: iizuka
 */

#include "btree/AbstractBtreeDataFactory.h"
#include "btree/DataNode.h"
#include "btree/BtreeStorage.h"
#include "btree/AbstractBtreeKey.h"

namespace alinous {

AbstractBtreeDataFactory::~AbstractBtreeDataFactory() {
}

void AbstractBtreeDataFactory::registerData(const AbstractBtreeKey* key, const IBlockObject* data, DataNode* dataNode, BtreeStorage* store) const {
	uint64_t dataFpos = dataNode->getDataFpos();
	if(dataFpos != 0){
		store->removeData(dataFpos);
	}

	dataFpos = store->storeData(data);
	dataNode->setDataFpos(dataFpos);
}

bool AbstractBtreeDataFactory::beforeRemove(DataNode* dataNode, BtreeStorage* store, const AbstractBtreeKey* key) const {
	return true;
}

} /* namespace alinous */
