/*
 * test_exceptions.cpp
 *
 *  Created on: 2020/04/13
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

TEST_GROUP(TestExceptionParseGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestExceptionParseGroup, throw01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/exception/throw01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	ThrowStatement* stmt = lang->throwStatement(); __STP(stmt);
	CHECK(!parser.hasError())

	int size = stmt->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	stmt->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestExceptionParseGroup, try01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/exception/try01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	TryStatement* stmt = lang->tryStatement(); __STP(stmt);
	CHECK(!parser.hasError())

	int size = stmt->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	stmt->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestExceptionParseGroup, try02){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/exception/try02.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	TryStatement* stmt = lang->tryStatement(); __STP(stmt);
	CHECK(!parser.hasError())

	int size = stmt->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	stmt->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}
