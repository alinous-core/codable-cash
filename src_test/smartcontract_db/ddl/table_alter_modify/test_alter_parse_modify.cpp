/*
 * test_alter_parse_modify.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "engine/compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"

TEST_GROUP(TestAlterParseModifyGroup) {
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

TEST(TestAlterParseModifyGroup, AlterAddPrimaryKeyCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/parse_modify/AlterAddPrimaryKeyCommand01.alns"))
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

TEST(TestAlterParseModifyGroup, AlterDropPrimaryKeyCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/parse_modify/AlterDropPrimaryKeyCommand01.alns"))
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

TEST(TestAlterParseModifyGroup, AlterModifyCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/parse_modify/AlterModifyCommand01.alns"))
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

TEST(TestAlterParseModifyGroup, AlterRenameColumnCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/parse_modify/AlterRenameColumnCommand01.alns"))
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

TEST(TestAlterParseModifyGroup, AlterRenameTableCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/parse_modify/AlterRenameTableCommand01.alns"))
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


