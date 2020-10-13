/*
 * test_exp_bit.cpp
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

TEST_GROUP(TestExpressionBitGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestExpressionBitGroup, bitand01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitand01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionBitGroup, bitand01bin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitand01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestExpressionBitGroup, bitor01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitor01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionBitGroup, bitor01bin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitor01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestExpressionBitGroup, bitexor01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitexor01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionBitGroup, bitexor01bin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitexor01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}


TEST(TestExpressionBitGroup, bitshift){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitshift.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())
}

TEST(TestExpressionBitGroup, bitshiftBin){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/expression_bit/bitshift.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	AbstractExpression* exp = lang->expression(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}
