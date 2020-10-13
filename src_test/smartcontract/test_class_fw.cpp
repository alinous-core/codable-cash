/*
 * test_class_fw.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "engine/sc/CompilationUnit.h"
#include "engine/compiler/SmartContractParser.h"
#include "engine/sc/exceptions.h"

TEST_GROUP(TestClassFwGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestClassFwGroup, exceptions){
	testException<MulformattedScBinaryException>();
}

TEST(TestClassFwGroup, exceptions01){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsStatement(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions02){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsType(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions03){
	Exception* ex = nullptr;
	try{
		CodeElement::checkNotNull(nullptr);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions04){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkKind(element, CodeElement::ARGUMENTS_LIST_DECLARE);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions05){
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(10, true); __STP(buff);
	buff->putShort(0xffff);
	buff->position(0);

	Exception* ex = nullptr;
	try{
		CodeElement::createFromBinary(buff);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions06){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsExp(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions07){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsSQLExp(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions08){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsJoinPart(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions09){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsImport(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions10){
	CompilationUnit element;

	Exception* ex = nullptr;
	try{
		element.getCompilationUnit();
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions11){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsJsonExp(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, exceptions12){
	CompilationUnit* element = new CompilationUnit();

	Exception* ex = nullptr;
	try{
		CodeElement::checkIsAlterCommand(element);
	}
	catch(Exception* e){
		ex = e;
	}
	CHECK(ex != nullptr)

	delete ex;
}

TEST(TestClassFwGroup, isExecutable){
	CompilationUnit* element = new CompilationUnit(); __STP(element);

	CHECK(element->isExecutable() == false)
}

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
	CodeElement* element = CodeElement::createFromBinary(buff); __STP(element);

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

