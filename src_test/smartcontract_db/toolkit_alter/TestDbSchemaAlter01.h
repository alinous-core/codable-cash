/*
 * TestDbSchemaAlter01.h
 *
 *  Created on: 2020/09/23
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER01_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER01_H_

#include "../toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlter01 : public TestDbSchemaBase {
public:
	TestDbSchemaAlter01(TestEnv* env);
	virtual ~TestDbSchemaAlter01();

	virtual void init(uint64_t memCapacity);

	void createTable();
	void insert01();

private:
	void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, int email_id);
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER01_H_ */
