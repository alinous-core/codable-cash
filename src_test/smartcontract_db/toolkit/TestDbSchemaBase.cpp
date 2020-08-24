/*
 * TestDbSchemaBase.cpp
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#include "TestDbSchemaBase.h"

#include "engine/CodableDatabase.h"

namespace codablecash {

TestDbSchemaBase::TestDbSchemaBase(TestEnv* env) {
	this->db = new CodableDatabase();
	this->env = env;
}

TestDbSchemaBase::~TestDbSchemaBase() {
	delete this->db;
	this->env = nullptr;
}

} /* namespace codablecash */
