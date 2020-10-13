/*
 * AlterDropIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropIndexCommand.h"

#include "base/UnicodeString.h"

#include "trx/transaction_log_alter/AlterDropIndexCommandLog.h"
#include "trx/transaction_log_alter/AbstractAlterCommandLog.h"

#include "vm/VirtualMachine.h"

#include "sql_join_parts/TableIdentifier.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableIndex.h"

#include "schema_table/table/CdbTableColumn.h"

using codablecash::CdbTableColumn;
namespace alinous {

AlterDropIndexCommand::AlterDropIndexCommand(const AlterDropIndexCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_INDEX){
	this->name = new UnicodeString(inst.name);
}

AlterDropIndexCommand::AlterDropIndexCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_INDEX) {
	this->name = nullptr;
}

AlterDropIndexCommand::~AlterDropIndexCommand() {
	delete this->name;
}

void AlterDropIndexCommand::setName(UnicodeString* name) noexcept {
	this->name = name;
}

int AlterDropIndexCommand::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);

	return total;
}

void AlterDropIndexCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_ALTER_DROP_INDEX);
	putString(out, this->name);
}

void AlterDropIndexCommand::fromBinary(ByteBuffer* in) {
	this->name = getString(in);
}

AbstractAlterCommandLog* AlterDropIndexCommand::getCommandLog() {
	AlterDropIndexCommandLog* log = new AlterDropIndexCommandLog();
	log->setCommand(new AlterDropIndexCommand(*this));

	return log;
}

void AlterDropIndexCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterDropIndexCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterDropIndexCommand::analyze(AnalyzeContext* actx) {
}

void AlterDropIndexCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterDropIndexCommandLog* thisLog = dynamic_cast<AlterDropIndexCommandLog*>(log);
	const AlterDropIndexCommand* command = thisLog->getCommand();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	tableId->inputDefaultSchema(defaultSchema);

	CdbTable* table = schemaManager->getTable(tableId, nullptr); // throws if Table does not exists;

	const UnicodeString* idxname = command->getName();
	CdbTableIndex* index = table->getIndexByName(idxname);
	if(index == nullptr){
		throw new CdbException(L"Index does not exist", __FILE__, __LINE__);
	}

	if(index->isPrimaryKey()){
		throw new CdbException(L"Can not delete primary key index, use ALTER TABLE DROP PRIMARY KEY, instead.", __FILE__, __LINE__);
	}

	if(index->getColumnLength() == 1 && index->isUnique() && index->getColumnAt(0)->isUnique()){
		throw new CdbException(L"Can not delete index used by unique column.", __FILE__, __LINE__);
	}
}

} /* namespace alinous */
