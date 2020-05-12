/*
 * test_sql_engine.cpp
 *
 *  Created on: 2020/05/10
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/File.h"
#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "engine/CdbException.h"
using namespace codablecash;


TEST_GROUP(TestDbEngineGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestDbEngineGroup, construct){
	File projectFolder = this->env->testCaseDir();
	CodableDatabase db;
}

TEST(TestDbEngineGroup, createDb01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	db.createDatabase(dbDir);
}

TEST(TestDbEngineGroup, createDb02){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	db.createDatabase(dbDir);

	db.loadDatabase(dbDir);
}

TEST(TestDbEngineGroup, createDbLoadError01){
	File testCaseFolder = this->env->testCaseDir();
	File* dbDir = testCaseFolder.get(L"db"); __STP(dbDir);
	CodableDatabase db;

	bool result = db.loadDatabase(dbDir);
	CHECK(!result)
}

TEST(TestDbEngineGroup, testEx){
	testException<CdbException>();
}

