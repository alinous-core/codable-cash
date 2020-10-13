/*
 * test_dom_parser.cpp
 *
 *  Created on: 2020/06/29
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "engine/compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"
#include "engine/sc_analyze/AnalyzedType.h"

using namespace alinous;

TEST_GROUP(TestDomParserGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

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

TEST(TestDomParserGroup, valuePair01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/variable/resources/json/valuepair01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	JsonKeyValuePairExpression* exp = lang->jsonKeyValuePair(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)

	AnalyzedType at = exp->getType(nullptr);
	CHECK(AnalyzedType::TYPE_DOM_VALUE_PAIR == at.getType())
}

TEST(TestDomParserGroup, valuePair02){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/variable/resources/json/valuepair02.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	JsonKeyValuePairExpression* exp = lang->jsonKeyValuePair(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)
}

TEST(TestDomParserGroup, valueArray01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/variable/resources/json/array01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	JsonArrayExpression* exp = lang->jsonArrayExpression(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)

	AnalyzedType at = exp->getType(nullptr);
	CHECK(AnalyzedType::TYPE_DOM_ARRAY == at.getType())
}

TEST(TestDomParserGroup, init01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/variable/resources/json/init01.alns"))

	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	JsonInitializerExpression* exp = lang->jsonInitializerExpression(); __STP(exp);

	CHECK(!parser.hasError())

	int size = exp->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	exp->toBinary(buff);
	CHECK(buff->position() == size)

	bool res = checkBinary(buff);
	CHECK(res)

	AnalyzedType at = exp->getType(nullptr);
	CHECK(AnalyzedType::TYPE_DOM == at.getType())
}

