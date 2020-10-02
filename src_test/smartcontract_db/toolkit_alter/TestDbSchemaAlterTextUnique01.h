/*
 * TestDbSchemaAlterTextUnique01.h
 *
 *  Created on: 2020/10/02
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXTUNIQUE01_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXTUNIQUE01_H_

#include "../toolkit/TestDbSchemaBase.h"

namespace codablecash {

class CdbTransaction;

class TestDbSchemaAlterTextUnique01 : public TestDbSchemaBase {
public:
	TestDbSchemaAlterTextUnique01(TestEnv* env);
	virtual ~TestDbSchemaAlterTextUnique01();
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERTEXTUNIQUE01_H_ */
