/*
 * RecordStore.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef TABLE_STORE_RECORDSTORE_H_
#define TABLE_STORE_RECORDSTORE_H_

namespace alinous {
class File;
}
using namespace alinous;

namespace codablecash {

class CdbTable;

class RecordStore {
public:
	RecordStore(const File* tableDir, const CdbTable* table);
	virtual ~RecordStore();

	void load();
private:
	File* tableDir;
	const CdbTable* table;
};

} /* namespace codablecash */

#endif /* TABLE_STORE_RECORDSTORE_H_ */
