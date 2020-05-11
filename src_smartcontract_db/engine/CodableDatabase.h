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

class CodableDatabase {
public:
	CodableDatabase();
	virtual ~CodableDatabase();

	void createDatabase(File* dbdir);
private:
	CdbTransactionManager* trxManager;
};

} /* namespace alinous */

#endif /* ENGINE_CODABLEDATABASE_H_ */
