/*
 * TableStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/TableStore.h"
#include "table_store/RecordStore.h"

namespace codablecash {

TableStore::TableStore() {
	this->recordStore = new RecordStore();

}

TableStore::~TableStore() {
	delete this->recordStore;
}

} /* namespace codablecash */
