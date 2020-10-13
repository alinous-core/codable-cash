/*
 * test_statement.cpp
 *
 *  Created on: 2019/03/01
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "engine/compiler/SmartContractParser.h"

#include "base/StackRelease.h"
#include "lang/sc_expression_literal/NullLiteral.h"

#include "alinous_lang/AlinousLang.h"

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

TEST_GROUP(TestStatementGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStatementGroup, substitute01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/substitute01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, substitute01bin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/substitute01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())

	int size = stmt->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	stmt->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestStatementGroup, substitute02){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/substitute02.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, valdec01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/valdec01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, valdec01bin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/valdec01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())

	int size = stmt->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	stmt->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}


TEST(TestStatementGroup, blank){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/blank.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, blankBin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/blank.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())

	int size = stmt->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	stmt->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestStatementGroup, expstatement){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/expstatement.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())
}

TEST(TestStatementGroup, expstatementBin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/statement/expstatement.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractStatement* stmt = lang->statement(); __STP(stmt);

	CHECK(!parser.hasError())

	int size = stmt->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	stmt->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

