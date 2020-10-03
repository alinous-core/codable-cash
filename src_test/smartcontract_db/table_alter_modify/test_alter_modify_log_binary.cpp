/*
 * test_alter_modify_log_binary.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"

#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/AbstractTransactionLog.h"

#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterModifyCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"
#include "sql_ddl_alter_modify/AlterDropPrimaryKeyCommand.h"
#include "sql_ddl_alter_modify/AlterModifyCommand.h"
#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"
#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"


TEST_GROUP(TestAlterModifyLogBinaryGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

static bool checkBinary(ByteBuffer* buff);

bool checkBinary(ByteBuffer* buff){
	int lastSize = buff->capacity();

	buff->position(0);
	AbstractTransactionLog* element = TransactionLogFactory::createFromBinary(buff); __STP(element);

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

TEST(TestAlterModifyLogBinaryGroup, AlterAddPrimaryKeyCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/parse_modify/AlterAddPrimaryKeyCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		TableIdentifier tableId;
		tableId.setTableName(new UnicodeString(L"table1"));

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AbstractAlterDdlCommand* cmd = stmt->getCmd();
		stmt->setCommand(nullptr);

		AlterAddPrimaryKeyCommandLog log;
		log.setCommand(dynamic_cast<AlterAddPrimaryKeyCommand*>(cmd));
		log.setTableIdentifier(&tableId);

		int size = log.binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		log.toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

TEST(TestAlterModifyLogBinaryGroup, AlterDropPrimaryKeyCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/parse_modify/AlterDropPrimaryKeyCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		TableIdentifier tableId;
		tableId.setTableName(new UnicodeString(L"table1"));

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AbstractAlterDdlCommand* cmd = stmt->getCmd();
		stmt->setCommand(nullptr);

		AlterDropPrimaryKeyCommandLog log;
		log.setCommand(dynamic_cast<AlterDropPrimaryKeyCommand*>(cmd));
		log.setTableIdentifier(&tableId);

		int size = log.binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		log.toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

TEST(TestAlterModifyLogBinaryGroup, AlterModifyCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/parse_modify/AlterModifyCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		TableIdentifier tableId;
		tableId.setTableName(new UnicodeString(L"table1"));

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AbstractAlterDdlCommand* cmd = stmt->getCmd();
		stmt->setCommand(nullptr);

		AlterModifyCommandLog log;
		log.setCommand(dynamic_cast<AlterModifyCommand*>(cmd));
		log.setTableIdentifier(&tableId);

		log.setDefaultStr(new UnicodeString(L"0"));

		int size = log.binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		log.toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

TEST(TestAlterModifyLogBinaryGroup, AlterRenameColumnCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/parse_modify/AlterRenameColumnCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		TableIdentifier tableId;
		tableId.setTableName(new UnicodeString(L"table1"));

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AbstractAlterDdlCommand* cmd = stmt->getCmd();
		stmt->setCommand(nullptr);

		AlterRenameColumnCommandLog log;
		log.setCommand(dynamic_cast<AlterRenameColumnCommand*>(cmd));
		log.setTableIdentifier(&tableId);

		int size = log.binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		log.toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

TEST(TestAlterModifyLogBinaryGroup, AlterRenameTableCommand01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/parse_modify/AlterRenameTableCommand01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		TableIdentifier tableId;
		tableId.setTableName(new UnicodeString(L"table1"));

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AbstractAlterDdlCommand* cmd = stmt->getCmd();
		stmt->setCommand(nullptr);

		AlterRenameTableCommandLog log;
		log.setCommand(dynamic_cast<AlterRenameTableCommand*>(cmd));
		log.setTableIdentifier(&tableId);

		int size = log.binarySize();
		ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

		log.toBinary(buff);
		CHECK(buff->position() == size)

		bool res = checkBinary(buff);
		CHECK(res)
	}
}

