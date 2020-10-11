/*
 * TestDbSchemaAlterModifyIndexCheck.h
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERMODIFYINDEXCHECK_H_
#define SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERMODIFYINDEXCHECK_H_

#include "../toolkit/TestDbSchemaBase.h"

namespace codablecash {

class TestDbSchemaAlterModifyIndexCheck: public TestDbSchemaBase {
public:
	explicit TestDbSchemaAlterModifyIndexCheck(TestEnv* env);
	virtual ~TestDbSchemaAlterModifyIndexCheck();

	virtual void init(uint64_t memCapacity);
	void createTable();
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_TOOLKIT_ALTER_TESTDBSCHEMAALTERMODIFYINDEXCHECK_H_ */
