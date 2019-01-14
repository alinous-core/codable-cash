/*
 * FeeTransactionsListValueFactory.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/FeeTransactionsListValueFactory.h"
#include "mempool/FeeTransactionsListValue.h"

#include "btree/DataNode.h"
#include "btree/BtreeStorage.h"
#include "base/StackRelease.h"


namespace codablecash {

FeeTransactionsListValueFactory::FeeTransactionsListValueFactory() {
}

FeeTransactionsListValueFactory::~FeeTransactionsListValueFactory() {
}

IBlockObject* FeeTransactionsListValueFactory::makeDataFromBinary(ByteBuffer* in) {
	return FeeTransactionsListValue::fromBinary(in);
}

void FeeTransactionsListValueFactory::registerData(const IBlockObject* data, DataNode* dataNode,
		BtreeStorage* store) const {
	uint64_t dataFpos = dataNode->getDataFpos();
	if(dataFpos != 0){
		IBlockObject* obj = store->loadData(dataFpos);
		StackRelease<IBlockObject> __st_obj(obj);

		FeeTransactionsListValue* baseValue = dynamic_cast<FeeTransactionsListValue*>(obj);
		const FeeTransactionsListValue* newValue = dynamic_cast<const FeeTransactionsListValue*>(data);
		baseValue->join(newValue);

		store->storeData(baseValue, dataFpos);

		return;
	}

	dataFpos = store->storeData(data);
	dataNode->setDataFpos(dataFpos);
}

bool FeeTransactionsListValueFactory::beforeRemove(DataNode* dataNode, BtreeStorage* store, const AbstractBtreeKey* key) const {
	// FIXME
	return true;
}

} /* namespace codablecash */


