/*
 * TestDbSchemaAlter04.h
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER04_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER04_H_

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlter04 : public TestDbSchemaBase {
public:
	explicit TestDbSchemaAlter04(TestEnv* env);
	virtual ~TestDbSchemaAlter04();

	virtual void init(uint64_t memCapacity);

	void createTable();
	void insert01();

private:
	void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, int email_id);
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTER04_H_ */
