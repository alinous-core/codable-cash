/*
 * TestDbSchemaAlterModifyIndexCheck.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "TestDbSchemaAlterModifyIndexCheck.h"

namespace codablecash {

TestDbSchemaAlterModifyIndexCheck::TestDbSchemaAlterModifyIndexCheck(TestEnv* env) : TestDbSchemaBase(env) {

}

TestDbSchemaAlterModifyIndexCheck::~TestDbSchemaAlterModifyIndexCheck() {

}

void TestDbSchemaAlterModifyIndexCheck::init(uint64_t memCapacity) {
	TestDbSchemaBase::init(memCapacity);
	createTable();
}

void TestDbSchemaAlterModifyIndexCheck::createTable() {
}

} /* namespace codablecash */
