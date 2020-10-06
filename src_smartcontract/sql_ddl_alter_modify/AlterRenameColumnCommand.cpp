/*
 * AlterRenameColumnCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"

#include "base/UnicodeString.h"

#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "vm/VirtualMachine.h"

#include "sql_join_parts/TableIdentifier.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"
namespace alinous {

AlterRenameColumnCommand::AlterRenameColumnCommand(const AlterRenameColumnCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_COLUMN){
	this->lastName = new UnicodeString(inst.lastName);
	this->newName = new UnicodeString(inst.newName);
}


AlterRenameColumnCommand::AlterRenameColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_COLUMN) {
	this->lastName = nullptr;
	this->newName = nullptr;
}

AlterRenameColumnCommand::~AlterRenameColumnCommand() {
	delete this->lastName;
	delete this->newName;
}

void AlterRenameColumnCommand::setLastName(UnicodeString* name) noexcept {
	this->lastName = name;
}

void AlterRenameColumnCommand::setNewName(UnicodeString* name) noexcept {
	this->newName = name;
}

int AlterRenameColumnCommand::binarySize() const {
	checkNotNull(this->lastName);
	checkNotNull(this->newName);

	int total = sizeof(uint16_t);
	total += stringSize(this->lastName);
	total += stringSize(this->newName);

	return total;
}

void AlterRenameColumnCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->lastName);
	checkNotNull(this->newName);

	out->putShort(CodeElement::DDL_ALTER_RENAME_COLUMN);
	putString(out, this->lastName);
	putString(out, this->newName);
}

void AlterRenameColumnCommand::fromBinary(ByteBuffer* in) {
	this->lastName = getString(in);
	this->newName = getString(in);
}

AbstractAlterCommandLog* AlterRenameColumnCommand::getCommandLog() {
	AlterRenameColumnCommandLog* log = new AlterRenameColumnCommandLog();
	log->setCommand(new AlterRenameColumnCommand(*this));

	return log;
}

void AlterRenameColumnCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterRenameColumnCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterRenameColumnCommand::analyze(AnalyzeContext* actx) {
}

void AlterRenameColumnCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterRenameColumnCommandLog* renameTableLog = dynamic_cast<AlterRenameColumnCommandLog*>(log);
	const AlterRenameColumnCommand* command = renameTableLog->getCommand();
	const UnicodeString* lastName = command->getLastName();
	const UnicodeString* newName = command->getNewName();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	tableId->inputDefaultSchema(defaultSchema);

	CdbTable* table = schemaManager->getTable(tableId, nullptr); // throws if Table does not exists;

	CdbTableColumn* column = table->getColumn(lastName);
	if(column == nullptr){
		throw new CdbException(L"Column does not exist.", __FILE__, __LINE__);
	}
	column = table->getColumn(newName);
	if(column != nullptr){
		throw new CdbException(L"Column already exists.", __FILE__, __LINE__);
	}
}

} /* namespace alinous */
