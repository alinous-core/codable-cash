/*
 * RollbackStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml/RollbackStatement.h"

#include "vm/vm_trx/VmTransactionHandler.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "vm/VirtualMachine.h"

#include "base/Exception.h"


namespace alinous {

RollbackStatement::RollbackStatement() : AbstractSQLStatement(CodeElement::DML_STMT_ROLLBACK) {
}

RollbackStatement::~RollbackStatement() {
}

void RollbackStatement::preAnalyze(AnalyzeContext* actx) {
}

void RollbackStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void RollbackStatement::analyze(AnalyzeContext* actx) {
}

int RollbackStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void RollbackStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DML_STMT_ROLLBACK);
}

void RollbackStatement::fromBinary(ByteBuffer* in) {
}

void RollbackStatement::interpret(VirtualMachine* vm) {
	VmTransactionHandler* handler = vm->getTransactionHandler();

	try{
		handler->rollback();
	}
	catch(Exception* e){
		DatabaseExceptionClassDeclare::throwException(e->getMessage(), vm, this);
		delete e;
	}
}

} /* namespace alinous */
