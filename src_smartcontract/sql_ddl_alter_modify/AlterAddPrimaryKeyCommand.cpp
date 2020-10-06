/*
 * AlterAddPrimaryKeyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"

#include "base/UnicodeString.h"

#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"

#include "vm/VirtualMachine.h"

#include "sql_join_parts/TableIdentifier.h"

#include "table/CdbTable.h"

#include "schema/SchemaManager.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "table/CdbTableColumn.h"
namespace alinous {

AlterAddPrimaryKeyCommand::AlterAddPrimaryKeyCommand(const AlterAddPrimaryKeyCommand& inst)
		: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_PRIMARY_KEY) {
	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* col = inst.list.get(i);

		this->list.addElement(new UnicodeString(col));
	}
}


AlterAddPrimaryKeyCommand::AlterAddPrimaryKeyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_PRIMARY_KEY){
}

AlterAddPrimaryKeyCommand::~AlterAddPrimaryKeyCommand() {
	this->list.deleteElements();
}

void AlterAddPrimaryKeyCommand::addColumn(UnicodeString* column) noexcept {
	this->list.addElement(column);
}

int AlterAddPrimaryKeyCommand::binarySize() const {
	int total = sizeof(uint16_t);

	int maxLoop = this->list.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		total += stringSize(col);
	}

	return total;
}

void AlterAddPrimaryKeyCommand::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DDL_ALTER_ADD_PRIMARY_KEY);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		putString(out, col);
	}
}

void AlterAddPrimaryKeyCommand::fromBinary(ByteBuffer* in) {
	int maxLoop =in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = getString(in);
		addColumn(col);
	}
}

AbstractAlterCommandLog* AlterAddPrimaryKeyCommand::getCommandLog() {
	AlterAddPrimaryKeyCommandLog* log = new AlterAddPrimaryKeyCommandLog();
	log->setCommand(new AlterAddPrimaryKeyCommand(*this));

	return log;
}

void AlterAddPrimaryKeyCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterAddPrimaryKeyCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterAddPrimaryKeyCommand::analyze(AnalyzeContext* actx) {
}

void AlterAddPrimaryKeyCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterAddPrimaryKeyCommandLog* dropPrimaryKeyLog = dynamic_cast<AlterAddPrimaryKeyCommandLog*>(log);
	const AlterAddPrimaryKeyCommand* command = dropPrimaryKeyLog->getCommand();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	tableId->inputDefaultSchema(defaultSchema);

	CdbTable* table = schemaManager->getTable(tableId, nullptr); // throws if Table does not exists;

	CdbTableIndex* pkey = table->getPrimaryKey();
	if(pkey != nullptr){
		throw new CdbException(L"Primary key already exists.", __FILE__, __LINE__);
	}

	const ArrayList<UnicodeString>* list = command->getColumns();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* columnName = list->get(i);

		CdbTableColumn* c = table->getColumn(columnName);
		if(c == nullptr){
			throw new CdbException(L"Primary key column does not exist.", __FILE__, __LINE__);
		}
	}
}

const ArrayList<UnicodeString>* AlterAddPrimaryKeyCommand::getColumns() const noexcept {
	return &this->list;
}

} /* namespace alinous */
