/*
 * BeginStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_dml/BeginStatement.h"

#include "vm/vm_trx/VmTransactionHandler.h"

#include "vm/VirtualMachine.h"

#include "base/Exception.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

namespace alinous {

BeginStatement::BeginStatement() : AbstractSQLStatement(CodeElement::DML_STMT_BEGIN) {
}

BeginStatement::~BeginStatement() {
}

void BeginStatement::preAnalyze(AnalyzeContext* actx) {
}

void BeginStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void BeginStatement::analyze(AnalyzeContext* actx) {
}

int BeginStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void BeginStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DML_STMT_BEGIN);
}

void BeginStatement::fromBinary(ByteBuffer* in) {
}

void BeginStatement::interpret(VirtualMachine* vm) {
	VmTransactionHandler* handler = vm->getTransactionHandler();

	try{
		handler->begin();
	}
	catch(Exception* e){
		DatabaseExceptionClassDeclare::throwException(e->getMessage(), vm, this);
		delete e;
	}
}

} /* namespace alinous */
