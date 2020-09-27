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
class BtreeScanner;

class AbstractBtreeKey;
class IBlockObject;
class BtreeKeyFactory;
class AbstractBtreeDataFactory;

typedef struct __btree_open_config {
	int numDataBuffer = 256;
	int numNodeBuffer = 512;
} BtreeOpenConfig;

class Btree {
public:
	Btree() = delete;
	Btree(const Btree& inst) = delete;
	Btree(const File* folder, const UnicodeString* name, DiskCacheManager* cacheManager, BtreeKeyFactory* factory, AbstractBtreeDataFactory* dfactory);
	virtual ~Btree();

	bool exists() const noexcept;
	void create(const BtreeConfig* config);

	static void clearFiles(const File* folder, const UnicodeString* name);

	void open(const BtreeOpenConfig* config);
	void close() noexcept;

	void putData(const AbstractBtreeKey* key, const IBlockObject* data);
	BtreeScanner* getScanner();
	IBlockObject* findByKey(const AbstractBtreeKey* key);

	void remove(const AbstractBtreeKey* key);

private:
	UnicodeString* name;
	File* folder;
	BtreeKeyFactory* factory;
	AbstractBtreeDataFactory* dfactory;

	BtreeStorage* store;
	DiskCacheManager* cacheManager;
	BtreeConfig* config;
};

} /* namespace alinous */

#endif /* BTREE_BTREE_H_ */
