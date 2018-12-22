/*
 * Btree.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_BTREE_H_
#define BTREE_BTREE_H_

namespace alinous {

class File;
class UnicodeString;
class BtreeStorage;
class DiskCacheManager;
class BtreeConfig;

class Btree {
public:
	Btree() = delete;
	Btree(File* folder, UnicodeString* name, DiskCacheManager* cacheManager);
	virtual ~Btree();

	void create(BtreeConfig* config);

private:
	UnicodeString* name;
	File* folder;
	BtreeStorage* store;
	DiskCacheManager* cacheManager;
};

} /* namespace alinous */

#endif /* BTREE_BTREE_H_ */
