/*
 * test_class_fw.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "sc/CompilationUnit.h"
#include "compiler/SmartContractParser.h"

TEST_GROUP(TestClassFwGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestClassFwGroup, construct){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/classfw/class.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	CHECK(!parser.hasError())

	delete unit;
}

TEST(TestClassFwGroup, constructBinary){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/classfw/class.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();

	int size = unit->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	unit->toBinary(buff);

	delete unit;
}



TEST(TestClassFwGroup, memberVariable){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/classfw/classMember.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	CHECK(!parser.hasError())

	delete unit;
}

TEST(TestClassFwGroup, methods){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/classfw/classMethod.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	CHECK(!parser.hasError())

	delete unit;
}
