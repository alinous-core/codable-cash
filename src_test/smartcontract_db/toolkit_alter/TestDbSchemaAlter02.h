/*
 * TestDbSchemaAlter02.h
 *
 *  Created on: 2020/09/23
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER02_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER02_H_

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlter02 : public TestDbSchemaBase {
public:
	explicit TestDbSchemaAlter02(TestEnv* env);
	virtual ~TestDbSchemaAlter02();

	virtual void init(uint64_t memCapacity);

	void createTable();
	void insert01();

private:
	void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, int email_id);
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER02_H_ */
