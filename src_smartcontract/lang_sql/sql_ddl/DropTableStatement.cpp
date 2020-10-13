/*
 * DropTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl/DropTableStatement.h"
#include "lang_sql/sql_join_parts/TableIdentifier.h"

#include "vm/VirtualMachine.h"

#include "vm/vm_trx/VmTransactionHandler.h"

#include "trx/transaction_log/DropTableLog.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "base/Exception.h"

#include "engine/CodableDatabase.h"

#include "schema_table/schema/SchemaManager.h"

#include "engine/CdbException.h"
namespace alinous {

DropTableStatement::DropTableStatement() : AbstractSQLStatement(CodeElement::DDL_DROP_TABLE) {
	this->tableId = nullptr;
}

DropTableStatement::~DropTableStatement() {
	delete this->tableId;
}

void DropTableStatement::preAnalyze(AnalyzeContext* actx) {

}

void DropTableStatement::analyze(AnalyzeContext* actx) {

}

void DropTableStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void DropTableStatement::setTableId(TableIdentifier* tableId) noexcept {
	this->tableId = tableId;
}

int DropTableStatement::binarySize() const {
	checkNotNull(this->tableId);

	int total = sizeof(uint16_t);
	total += this->tableId->binarySize();

	return total;
}

void DropTableStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableId);

	out->putShort(CodeElement::DDL_DROP_TABLE);
	this->tableId->toBinary(out);
}

void DropTableStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_TABLE_ID);
	this->tableId = dynamic_cast<TableIdentifier*>(element);
}

void DropTableStatement::interpret(VirtualMachine* vm) {
	DropTableLog* cmd = new DropTableLog();
	cmd->setTableId(this->tableId);

	VmTransactionHandler* handler = vm->getTransactionHandler();
	try{
		validateCommandLog(vm, cmd);
		handler->dropTable(cmd);
	}
	catch(Exception* e){
		DatabaseExceptionClassDeclare::throwException(e->getMessage(), vm, this);
		delete e;
		delete cmd;
	}
}

void DropTableStatement::validateCommandLog(VirtualMachine* vm, DropTableLog* cmd) {
	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* currentSchema = vm->getCurrentSchema();
	cmd->inputDefaultSchema(currentSchema);

	const TableIdentifier* tableId = cmd->getTableId();

	if(!schemaManager->hasTable(tableId)){
		throw new CdbException(L"Table does not exist.", __FILE__, __LINE__);
	}

}


} /* namespace alinous */
