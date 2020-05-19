/*
 * TableStore.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_TABLESTORE_H_
#define TABLE_STORE_TABLESTORE_H_

namespace alinous {
class File;
}

using namespace alinous;

namespace codablecash {

class CdbTable;
class RecordStore;
class CdbOid;

class TableStore {
public:
	TableStore(const File* baseDir, const CdbTable* table);
	virtual ~TableStore();

	const CdbOid* getOid() const noexcept;

	void createTable();
	void loadTable();
private:
	File* baseDir;
	const CdbTable* table;

	RecordStore* recordStore;

};

} /* namespace codablecash */

#endif /* TABLE_STORE_TABLESTORE_H_ */
