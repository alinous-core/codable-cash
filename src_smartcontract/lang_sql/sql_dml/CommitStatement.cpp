/*
 * CommitStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml/CommitStatement.h"

#include "vm/VirtualMachine.h"

#include "vm/vm_trx/VmTransactionHandler.h"

#include "base/Exception.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

namespace alinous {

CommitStatement::CommitStatement() : AbstractSQLStatement(CodeElement::DML_STMT_COMMIT) {

}

CommitStatement::~CommitStatement() {
}

void CommitStatement::preAnalyze(AnalyzeContext* actx) {
}

void CommitStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void CommitStatement::analyze(AnalyzeContext* actx) {
}

int CommitStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void CommitStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DML_STMT_COMMIT);
}

void CommitStatement::fromBinary(ByteBuffer* in) {
}

void CommitStatement::interpret(VirtualMachine* vm) {
	VmTransactionHandler* handler = vm->getTransactionHandler();

	try{
		handler->commit();
	}
	catch(Exception* e){
		handler->rollback(true);

		DatabaseExceptionClassDeclare::throwException(e->getMessage(), vm, this);
		delete e;
	}
}

} /* namespace alinous */
