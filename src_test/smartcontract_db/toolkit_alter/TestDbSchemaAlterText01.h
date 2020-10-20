/*
 * TestDbSchemaAlterText01.h
 *
 *  Created on: 2020/10/02
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXT01_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXT01_H_

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlterText01 : public TestDbSchemaBase {
public:
	explicit TestDbSchemaAlterText01(TestEnv* env);
	virtual ~TestDbSchemaAlterText01();

	virtual void init(uint64_t memCapacity);

	void createTable();
	void insert01();

private:
	void insertRecord(CdbTransaction* trx, int id, const wchar_t* name, int email_id);
};

} /* namespace alinous */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXT01_H_ */
