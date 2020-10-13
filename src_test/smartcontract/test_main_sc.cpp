/*
 * test_main_sc.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

using namespace alinous;

TEST_GROUP(TestSmartContractGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestSmartContractGroup, construct){
	SmartContract* sc = new SmartContract();
	delete sc;
}

TEST(TestSmartContractGroup, newFile){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/hello.alns"))

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length, projectFolder, sourceFile);

	delete sc;
}


