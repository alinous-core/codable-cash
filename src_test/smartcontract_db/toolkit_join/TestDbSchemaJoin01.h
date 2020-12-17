/*
 * TestDbSchemaJoin01.h
 *
 *  Created on: 2020/12/17
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_JOIN_TESTDBSCHEMAJOIN01_H_
#define SMARTCONTRACT_DB_TOOLKIT_JOIN_TESTDBSCHEMAJOIN01_H_

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"

namespace codablecash {

class TestDbSchemaJoin01 : public TestDbSchemaBase {
public:
	explicit TestDbSchemaJoin01(TestEnv* env);
	virtual ~TestDbSchemaJoin01();

	virtual void init(uint64_t memCapacity);

private:
	void createTable();
	void createTestTable1();
	void createTestTable2();
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_JOIN_TESTDBSCHEMAJOIN01_H_ */
