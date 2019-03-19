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

static bool checkBinary(ByteBuffer* buff){
	int lastSize = buff->capacity();

	buff->position(0);
	CodeElement* element = CodeElement::createFromBinary(buff);

	int size = element->binarySize();
	if(lastSize != size){
		return false;
	}

	ByteBuffer* buff2 = ByteBuffer::allocateWithEndian(size, true); __STP(buff2);
	element->toBinary(buff2);

	if(buff2->position() != size){
		return false;
	}

	return Mem::memcmp(buff->array(), buff2->array(), size) == 0;
}

TEST(TestClassFwGroup, constructBinary){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/classfw/class.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();

	int size = unit->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	unit->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)

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

TEST(TestClassFwGroup, memberVariableBinary){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/classfw/classMember.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	CHECK(!parser.hasError())

	int size = unit->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	unit->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)

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

TEST(TestClassFwGroup, methodsBinary){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/classfw/classMethod.alns"))

	SmartContractParser parser(sourceFile);
	CompilationUnit* unit = parser.parse();
	CHECK(!parser.hasError())

	int size = unit->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	unit->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)

	delete unit;
}

