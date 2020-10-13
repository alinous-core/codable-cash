/*
 * test_parser.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "engine/compiler/SmartContractParser.h"
#include "engine/sc/CompilationUnit.h"

using namespace alinous;

TEST_GROUP(TestParserGroup) {
	TEST_SETUP(){
		this->env->setup();
	}
	TEST_TEARDOWN(){
		this->env->teardown();
	}
};


TEST(TestParserGroup, construct){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/hello.alns"))

	bool exists = sourceFile->exists();
	CHECK(exists);

	SmartContractParser parser(sourceFile);
}

TEST(TestParserGroup, parseTest){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/hello.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	delete unit;
}

TEST(TestParserGroup, parseError01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/helloerr1.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	if(unit != nullptr){
		delete unit;
	}

	CHECK(parser.hasError())
}


TEST(TestParserGroup, lexError01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/helloerrlex.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	if(unit != nullptr){
		delete unit;
	}

	CHECK(parser.hasError())
}

TEST(TestParserGroup, lexError02){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/helloerrlexeof.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	if(unit != nullptr){
		delete unit;
	}

	CHECK(parser.hasError())
}


TEST(TestParserGroup, lexError03){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/helloerrlexeof2.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	if(unit != nullptr){
		delete unit;
	}

	CHECK(parser.hasError())
	CHECK(parser.hasLexError())
}
