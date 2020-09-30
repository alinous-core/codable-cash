/*
 * CodableDatabase.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef ENGINE_CODABLEDATABASE_H_
#define ENGINE_CODABLEDATABASE_H_

#include <cstdint>

namespace alinous {
class File;
class UnicodeString;
}
using namespace alinous;

namespace codablecash {
class CdbTransactionManager;
class SchemaManager;
class CdbTransaction;
class CdbStorageManager;
class ReadLockHandle;
class WriteLockHandle;
class DatabaseLevelLock;
class CdbLocalCacheManager;
class LocalOidFactory;

class CodableDatabase {
public:
	CodableDatabase();
	virtual ~CodableDatabase();

	void createDatabase(File* dbdir);
	bool loadDatabase(const File* dbdir);
	bool loadDatabase(const File* dbdir, const File* tmpdir);
	void closeDatabase() noexcept;

	CdbTransaction* newTransaction();

	CdbStorageManager* getStorageManager() const noexcept;
	SchemaManager* getSchemaManager() const noexcept;

	uint64_t getSchemaObjectVersionId() const noexcept;

	ReadLockHandle* databaseReadLock();
	WriteLockHandle* databaseWriteLock();

	CdbTransactionManager* getTransactionxManager() const noexcept {
		return trxManager;
	}

	CdbLocalCacheManager* getLocalCacheManager() const noexcept {
		return this->localCacheManager;
	}

	LocalOidFactory* getLocalOidFactory() const noexcept {
		return localOidFactory;
	}

private:
	void checkDatabaseLoaded() const;

private:
	CdbTransactionManager* trxManager;
	SchemaManager* schema;
	CdbStorageManager* store;

	LocalOidFactory* localOidFactory;
	CdbLocalCacheManager* localCacheManager;

	DatabaseLevelLock* dbLevelLock;

	File* loadedFile;
};

} /* namespace alinous */

#endif /* ENGINE_CODABLEDATABASE_H_ */
