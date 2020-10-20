/*
 * TestDbSchemaAlterModifyIndexCheck.h
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERMODIFYINDEXCHECK_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERMODIFYINDEXCHECK_H_

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlterModifyIndexCheck: public TestDbSchemaBase {
public:
	explicit TestDbSchemaAlterModifyIndexCheck(TestEnv* env);
	virtual ~TestDbSchemaAlterModifyIndexCheck();

	virtual void init(uint64_t memCapacity);
	void createTable();

	void insert01();
	void insert02();

private:
	void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, int email_id, const wchar_t* comment);
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERMODIFYINDEXCHECK_H_ */
