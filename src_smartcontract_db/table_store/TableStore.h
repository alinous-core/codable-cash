/*
 * TableStore.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_TABLESTORE_H_
#define TABLE_STORE_TABLESTORE_H_

#include "base/HashMap.h"
#include "base/ArrayList.h"

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
class CdbTableIndex;
class ColumnModifyContext;

class TableStore {
public:
	TableStore(DiskCacheManager* cacheManager, const File* baseDir, const CdbTable* table);
	virtual ~TableStore();

	const CdbOid* getOid() const noexcept;

	void createTable();
	void loadTable();
	const CdbTable* getTable() const noexcept;

	void insert(const CdbRecord* rec);
	void validateRecord(CdbRecord* rec);

	void modifyRecords(const ColumnModifyContext* ctx);
	void buildIndex(CdbTableIndex* index);
	void buildAllIndexes();

	RecordStore* getRecordStore() const noexcept {
		return this->recordStore;
	}

	void addIndex(const CdbTableIndex* index);
	void removeIndex(const CdbTableIndex* index);
	void resetAllIndexes();

	IndexStore* getIndexStore(const CdbOid* indexoid) const noexcept;

	CdbRecord* findRecord(const CdbOid* recordOid);

private:
	void validateRecordColumnValue(CdbTableColumn* meta, AbstractCdbValue* value);
	void addToIndexes(const CdbRecord* rec);
	void addRecord2Index(const ArrayList<IndexStore>* indexStoreList, const CdbRecord* rec);

private:
	DiskCacheManager* cacheManager;

	File* baseDir;
	const CdbTable* table;

	RecordStore* recordStore;
	HashMap<CdbOid, IndexStore>* indexStores;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_TABLESTORE_H_ */
