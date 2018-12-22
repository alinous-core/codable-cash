/*
 * BtreeStorage.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_BTREESTORAGE_H_
#define BTREE_BTREESTORAGE_H_

namespace alinous {

class UnicodeString;
class File;
class BlockFileStore;
class DiskCacheManager;
class BtreeConfig;

class BtreeStorage {
public:
	BtreeStorage(File* folder, UnicodeString* name);
	virtual ~BtreeStorage();

	void create(DiskCacheManager* cacheManager, BtreeConfig* config);
private:
	UnicodeString* name;
	File* folder;
	BlockFileStore* store;
};

} /* namespace alinous */

#endif /* BTREE_BTREESTORAGE_H_ */
