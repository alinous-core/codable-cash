/*
 * AlterAddColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddColumnCommand.h"

#include "sql_ddl/DdlColumnDescriptor.h"

#include "vm/VirtualMachine.h"

#include "sql_join_parts/TableIdentifier.h"

#include "transaction_log_alter/AbstractAlterCommandLog.h"
#include "transaction_log_alter/AlterAddColumnCommandLog.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"

#include "table_store/CdbStorageManager.h"
#include "table_store/TableStore.h"
#include "table_store/RecordStore.h"

#include "base/UnicodeString.h"

#include "scan/RecordScanner.h"

namespace alinous {

AlterAddColumnCommand::AlterAddColumnCommand(const AlterAddColumnCommand& inst)
				: AbstractAlterDdlWithTypeDesc(CodeElement::DDL_ALTER_ADD_COLUMN) {
	this->columnDescriptor = copyColumnDescriptor(inst.columnDescriptor);
	this->longValue = inst.longValue;
}

AlterAddColumnCommand::AlterAddColumnCommand() : AbstractAlterDdlWithTypeDesc(CodeElement::DDL_ALTER_ADD_COLUMN) {

}

AlterAddColumnCommand::~AlterAddColumnCommand() {

}

int AlterAddColumnCommand::binarySize() const {
	checkNotNull(this->columnDescriptor);

	int total = sizeof(uint16_t);
	total += this->columnDescriptor->binarySize();

	return total;
}

void AlterAddColumnCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->columnDescriptor);

	out->putShort(CodeElement::DDL_ALTER_ADD_COLUMN);
	this->columnDescriptor->toBinary(out);
}

void AlterAddColumnCommand::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::DDL_COLMUN_DESC);

	this->columnDescriptor = dynamic_cast<DdlColumnDescriptor*>(element);
}

AbstractAlterCommandLog* AlterAddColumnCommand::getCommandLog() {
	AlterAddColumnCommandLog* log = new AlterAddColumnCommandLog();
	log->setCommand(new AlterAddColumnCommand(*this));

	return log;
}

void AlterAddColumnCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterAddColumnCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterAddColumnCommand::analyze(AnalyzeContext* actx) {
	analyzeLengthOfValiable(actx);

	AbstractSQLExpression* defaultValue = this->columnDescriptor->getDefaultValue();
	if(defaultValue != nullptr){
		defaultValue->analyze(actx);
	}
}

void AlterAddColumnCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterAddColumnCommandLog* thisLog = dynamic_cast<AlterAddColumnCommandLog*>(log);
	AlterAddColumnCommand* command = thisLog->getCommand();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	tableId->inputDefaultSchema(defaultSchema);

	CdbTable* table = schemaManager->getTable(tableId, nullptr); // throws if Table does not exists;

	const DdlColumnDescriptor* colDesc = command->getColumnDescriptor();
	const UnicodeString* colName = colDesc->getName();

	CdbTableColumn* c = table->getColumn(colName);
	if(c != nullptr){
		throw new CdbException(L"Column already exists", __FILE__, __LINE__);
	}

	UnicodeString* str = interpretDefaultString(vm);
	command->setDefaultValueStr(str);

	// check unique
	if(colDesc->isUnique()){
		CdbStorageManager* storageManager = db->getStorageManager();
		TableStore* store = storageManager->getTableStore(table->getOid());

		checkRecordCount(store);
	}
}

void AlterAddColumnCommand::checkRecordCount(TableStore* store) {
	RecordScanner scanner(store);

	scanner.start();

	int count = 0;
	while(scanner.hasNext()){
		const CdbRecord* record = scanner.next();

		count++;
		if(count > 1){
			throw new CdbException(L"Unique column requires unique data.", __FILE__, __LINE__);
		}
	}
}

} /* namespace alinous */
