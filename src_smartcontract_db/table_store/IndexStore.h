/*
 * IndexStore.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_INDEXSTORE_H_
#define TABLE_STORE_INDEXSTORE_H_

namespace alinous {
class File;
}
using namespace alinous;

namespace codablecash {

class CdbTable;
class CdbTableIndex;
class CdbOid;

class IndexStore {
public:
	IndexStore(const File* tableDir, const CdbTable* table, const CdbTableIndex* index);
	virtual ~IndexStore();

	static void createStore(const File* tableDir, const CdbTable* table, const CdbTableIndex* index);
	void load();

	const CdbOid* getIndexOid() const noexcept;
private:
	File* tableDir;
	const CdbTable* table;
	const CdbTableIndex* index;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_INDEXSTORE_H_ */
