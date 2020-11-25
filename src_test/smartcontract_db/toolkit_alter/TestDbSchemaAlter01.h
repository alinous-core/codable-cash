/*
 * TestDbSchemaAlter01.h
 *
 *  Created on: 2020/09/23
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER01_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER01_H_

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlter01 : public TestDbSchemaBase {
public:
	explicit TestDbSchemaAlter01(TestEnv* env);
	virtual ~TestDbSchemaAlter01();

	virtual void init(uint64_t memCapacity);

	void createTable();
	void insert01();
	void insert02();
	void insert03();

private:
	void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, int email_id);
	void insertRecord02(CdbTransaction* trx, int id, const wchar_t* name);
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER01_H_ */
