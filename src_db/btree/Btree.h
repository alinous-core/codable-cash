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

typedef struct __btree_open_config {
	int numDataBuffer = 256;
	int numNodeBuffer = 512;
} BtreeOpenConfig;

class Btree {
public:
	Btree() = delete;
	Btree(const Btree& inst) = delete;
	Btree(File* folder, UnicodeString* name, DiskCacheManager* cacheManager);
	virtual ~Btree();

	void create(BtreeConfig* config);

	void open(BtreeOpenConfig* config);
	void close();

private:
	UnicodeString* name;
	File* folder;
	BtreeStorage* store;
	DiskCacheManager* cacheManager;
	BtreeConfig* config;
};

} /* namespace alinous */

#endif /* BTREE_BTREE_H_ */
