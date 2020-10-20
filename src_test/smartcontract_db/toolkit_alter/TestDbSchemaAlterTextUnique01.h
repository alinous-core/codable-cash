/*
 * TestDbSchemaAlterTextUnique01.h
 *
 *  Created on: 2020/10/02
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXTUNIQUE01_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXTUNIQUE01_H_

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlterTextUnique01 : public TestDbSchemaBase {
public:
	explicit TestDbSchemaAlterTextUnique01(TestEnv* env);
	virtual ~TestDbSchemaAlterTextUnique01();

	virtual void init(uint64_t memCapacity);

	void createTable();
	void insert01();
	void insert02();
	void insert03();

private:
	void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, int email_id);
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXTUNIQUE01_H_ */
