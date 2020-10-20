/*
 * test_alter_parse.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "engine/compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestAlterParseGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};
static bool checkBinary(ByteBuffer* buff);

bool checkBinary(ByteBuffer* buff){
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

TEST(TestAlterParseGroup, AlterAddColumnCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter/resources/parse/alterAddColumn01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		int size = stmt->binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		stmt->toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

TEST(TestAlterParseGroup, AlterAddIndexCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter/resources/parse/alterAddIndexCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		int size = stmt->binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		stmt->toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

TEST(TestAlterParseGroup, AlterDropColumnCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter/resources/parse/alterDropColumnCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		int size = stmt->binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		stmt->toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

TEST(TestAlterParseGroup, AlterDropIndexCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter/resources/parse/alterDropIndexCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		int size = stmt->binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		stmt->toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}

}
