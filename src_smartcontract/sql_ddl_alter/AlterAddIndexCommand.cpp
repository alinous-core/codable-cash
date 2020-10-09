/*
 * AlterAddIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddIndexCommand.h"

#include "base/UnicodeString.h"
#include "base/ArrayList.h"

#include "transaction_log_alter/AlterAddIndexCommandLog.h"

#include "vm/VirtualMachine.h"

#include "sql_join_parts/TableIdentifier.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbOid.h"
#include "engine/CdbException.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "sql_ddl_alter/IndexChecker.h"

using namespace codablecash;

namespace alinous {

AlterAddIndexCommand::AlterAddIndexCommand(const AlterAddIndexCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_INDEX) {
	this->name = new UnicodeString(inst.name);
	this->unique = inst.unique;

	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* col = inst.list.get(i);

		addColumn(new UnicodeString(col));
	}
}

AlterAddIndexCommand::AlterAddIndexCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_INDEX) {
	this->name = nullptr;
	this->unique = false;
}

AlterAddIndexCommand::~AlterAddIndexCommand() {
	delete this->name;
	this->list.deleteElements();
}

void AlterAddIndexCommand::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void AlterAddIndexCommand::setUnique(bool unique) noexcept {
	this->unique = unique;
}

void AlterAddIndexCommand::addColumn(UnicodeString* colName) noexcept {
	this->list.addElement(colName);
}

int AlterAddIndexCommand::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);
	total += sizeof(uint8_t);

	int maxLoop = this->list.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		total += stringSize(col);
	}

	return total;
}

void AlterAddIndexCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_ALTER_ADD_INDEX);
	putString(out, this->name);
	out->put(this->unique ? 1 : 0);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		putString(out, col);
	}
}

void AlterAddIndexCommand::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	uint8_t bl = in->get();
	this->unique = (bl >= 1);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = getString(in);
		addColumn(col);
	}
}

AbstractAlterCommandLog* AlterAddIndexCommand::getCommandLog() {
	AlterAddIndexCommandLog* log = new AlterAddIndexCommandLog();
	log->setCommand(new AlterAddIndexCommand(*this));

	return log;
}

void AlterAddIndexCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterAddIndexCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterAddIndexCommand::analyze(AnalyzeContext* actx) {
}

void AlterAddIndexCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterAddIndexCommandLog* thisLog = dynamic_cast<AlterAddIndexCommandLog*>(log);
	const AlterAddIndexCommand* command = thisLog->getCommand();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	tableId->inputDefaultSchema(defaultSchema);

	CdbTable* table = schemaManager->getTable(tableId, nullptr); // throws if Table does not exists;

	const UnicodeString* tableName =table->getName();
	const UnicodeString* idxname = command->getName();

	if(tableName->equals(idxname)){
		throw new CdbException(L"Index can not use table name.", __FILE__, __LINE__);
	}

	bool unique = command->isUnique();

	ArrayList<const CdbOid> oidlist;
	const ArrayList<UnicodeString>* colList = command->getList();

	int maxLoop = colList->size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* colstr = colList->get(i);

		const CdbTableColumn* c = table->getColumn(colstr);
		if(c == nullptr){
			throw new CdbException(L"Column does not exist", __FILE__, __LINE__);
		}


		oidlist.addElement(c->getOid());
	}

	CdbTableIndex* index = table->getIndexByColumnOidsStrict(&oidlist, unique);
	if(index != nullptr){
		throw new CdbException(L"Index with same column & uniqueness exists", __FILE__, __LINE__);
	}

	index = table->getIndexByName(idxname);
	if(index != nullptr){
		throw new CdbException(L"Index with same name exists", __FILE__, __LINE__);
	}

	// check data is unique
	if(unique){
		IndexChecker indexChecker(db);
		bool result = indexChecker.checkUnique(table, &oidlist, false);
		if(!result){
			throw new CdbException(L"Unique index requires unique data.", __FILE__, __LINE__);
		}
	}
}

} /* namespace alinous */
