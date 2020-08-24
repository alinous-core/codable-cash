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
#include "vm/VirtualMachine.h"

namespace codablecash {

TestDbSchemaBase::TestDbSchemaBase(TestEnv* env) {
	this->env = env;
	this->dbDir = nullptr;
	this->vm = nullptr;
}

TestDbSchemaBase::~TestDbSchemaBase() {
	this->env = nullptr;
	delete this->dbDir;
	delete this->vm;
}

void TestDbSchemaBase::init() {
	init(1024 * 10);
}

void TestDbSchemaBase::init(uint64_t memCapacity) {
	this->vm = new VirtualMachine(memCapacity);

	createDb();

	this->vm->loadDatabase(this->dbDir);
}

CodableDatabase* TestDbSchemaBase::getDatabase() const noexcept {
	return this->vm->getDb();
}

void TestDbSchemaBase::createDb() {
	File testCaseFolder = this->env->testCaseDir();
	this->dbDir = testCaseFolder.get(L"db");
	{
		CodableDatabase db;
		db.createDatabase(this->dbDir);
	}
}

} /* namespace codablecash */
