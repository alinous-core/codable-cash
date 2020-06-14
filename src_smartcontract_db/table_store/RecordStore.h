/*
 * RecordStore.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_RECORDSTORE_H_
#define TABLE_STORE_RECORDSTORE_H_

namespace alinous {
class DiskCacheManager;
class File;
class Btree;
}
using namespace alinous;

namespace codablecash {

class CdbTable;
class CdbRecord;

class RecordStore {
public:
	RecordStore(DiskCacheManager* cacheManager, const File* tableDir, const CdbTable* table);
	virtual ~RecordStore();

	static void createStore(const File* tableDir, const CdbTable* table, DiskCacheManager* cacheManager);

	void load();
	void close() noexcept;

	void insert(const CdbRecord* rec);

	Btree* getBtree() const noexcept {
		return this->btree;
	}
private:
	DiskCacheManager* cacheManager;
	File* tableDir;
	const CdbTable* table;

	Btree* btree;
	bool opened;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_RECORDSTORE_H_ */
