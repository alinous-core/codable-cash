/*
 * TestDbSchema01.h
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMA01_H_
#define SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMA01_H_

#include "TestDbSchemaBase.h"

namespace codablecash {

class TestDbSchema01 : public TestDbSchemaBase {
public:
	explicit TestDbSchema01(TestEnv* env);
	virtual ~TestDbSchema01();


};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_TESTDBSCHEMA01_H_ */
