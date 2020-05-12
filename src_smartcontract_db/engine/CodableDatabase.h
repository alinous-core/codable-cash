/*
 * CodableDatabase.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef ENGINE_CODABLEDATABASE_H_
#define ENGINE_CODABLEDATABASE_H_

namespace alinous {
class File;
class UnicodeString;
}
using namespace alinous;

namespace codablecash {
class CdbTransactionManager;
class Schema;
class CdbTransaction;

class CodableDatabase {
public:
	CodableDatabase();
	virtual ~CodableDatabase();

	void createDatabase(File* dbdir);
	bool loadDatabase(const File* dbdir);
	void closeDatabase() noexcept;

	CdbTransaction* newTransaction();
private:
	CdbTransactionManager* trxManager;
	Schema* schema;
	File* loadedFile;
};

} /* namespace alinous */

#endif /* ENGINE_CODABLEDATABASE_H_ */
