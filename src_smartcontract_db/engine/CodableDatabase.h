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

class CodableDatabase {
public:
	CodableDatabase();
	virtual ~CodableDatabase();

	void createDatabase(File* dbdir);
	bool loadDatabase(const File* dbdir);
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

private:
	void checkDatabaseLoaded() const;

private:
	CdbTransactionManager* trxManager;
	SchemaManager* schema;
	CdbStorageManager* store;

	DatabaseLevelLock* dbLevelLock;

	File* loadedFile;
};

} /* namespace alinous */

#endif /* ENGINE_CODABLEDATABASE_H_ */
