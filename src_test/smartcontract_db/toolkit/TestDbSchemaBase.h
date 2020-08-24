/*
 * TestDbSchemaBase.h
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_
#define SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_


namespace alinous {
class TestEnv;
class File;
}
using namespace alinous;


namespace codablecash {

class CodableDatabase;

class TestDbSchemaBase {
public:
	explicit TestDbSchemaBase(TestEnv* env);
	virtual ~TestDbSchemaBase();

	CodableDatabase* getDb() const noexcept {
		return db;
	}

	void initDb();
protected:
	void createDb();

protected:
	CodableDatabase* db;
	TestEnv* env;

	File* dbDir;
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMABASE_H_ */
