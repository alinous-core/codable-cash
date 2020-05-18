/*
 * TableStore.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_TABLESTORE_H_
#define TABLE_STORE_TABLESTORE_H_

namespace codablecash {

class RecordStore;

class TableStore {
public:
	TableStore();
	virtual ~TableStore();

private:
	RecordStore* recordStore;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_TABLESTORE_H_ */
