/*
 * TableStore.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_TABLESTORE_H_
#define TABLE_STORE_TABLESTORE_H_

#include "base/HashMap.h"

namespace alinous {
class File;
class DiskCacheManager;
}
using namespace alinous;

namespace codablecash {

class CdbTable;
class RecordStore;
class CdbOid;
class IndexStore;
class CdbRecord;
class AbstractCdbValue;
class CdbTableColumn;

class TableStore {
public:
	TableStore(DiskCacheManager* cacheManager, const File* baseDir, const CdbTable* table);
	virtual ~TableStore();

	const CdbOid* getOid() const noexcept;

	void createTable();
	void loadTable();

	void insert(const CdbRecord* rec);
	void validateRecord(CdbRecord* rec);

	RecordStore* getRecordStore() const noexcept {
		return this->recordStore;
	}

	const CdbTable* getTable() const noexcept;

	IndexStore* getIndexStore(const CdbOid* oid) const noexcept;

	CdbRecord* findRecord(const CdbOid* recordOid);

private:
	void validateRecordColumnValue(CdbTableColumn* meta, AbstractCdbValue* value);
private:
	DiskCacheManager* cacheManager;

	File* baseDir;
	const CdbTable* table;

	RecordStore* recordStore;
	HashMap<CdbOid, IndexStore>* indexStores;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_TABLESTORE_H_ */
