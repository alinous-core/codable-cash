/*
 * TestDbSchemaBase.cpp
 *
 *  Created on: 2020/08/24
 *      Author: iizuka
 */

#include "TestDbSchemaBase.h"

#include "engine/CodableDatabase.h"

#include "base_io/File.h"
#include "../../test_utils/TestEnv.h"

namespace codablecash {

TestDbSchemaBase::TestDbSchemaBase(TestEnv* env) {
	this->db = new CodableDatabase();
	this->env = env;
	this->dbDir = nullptr;
}

TestDbSchemaBase::~TestDbSchemaBase() {
	delete this->db;
	this->env = nullptr;
	delete this->dbDir;
}

void TestDbSchemaBase::initDb() {
	createDb();

}

void TestDbSchemaBase::createDb() {
	File testCaseFolder = this->env->testCaseDir();
	this->dbDir = testCaseFolder.get(L"db");

	this->db->createDatabase(this->dbDir);
	this->db->loadDatabase(this->dbDir);
}

} /* namespace codablecash */
