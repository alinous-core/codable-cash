/*
 * AlterDropPrimaryKeyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterDropPrimaryKeyCommand.h"

#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"

namespace alinous {

alinous::AlterDropPrimaryKeyCommand::AlterDropPrimaryKeyCommand(const AlterDropPrimaryKeyCommand& inst)
	: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_PRIMARY_KEY) {
}

AlterDropPrimaryKeyCommand::AlterDropPrimaryKeyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_PRIMARY_KEY) {

}

AlterDropPrimaryKeyCommand::~AlterDropPrimaryKeyCommand() {

}

int AlterDropPrimaryKeyCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropPrimaryKeyCommand::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DDL_ALTER_DROP_PRIMARY_KEY);
}

void AlterDropPrimaryKeyCommand::fromBinary(ByteBuffer* in) {
}

AbstractAlterCommandLog* AlterDropPrimaryKeyCommand::getCommandLog() {
	AlterDropPrimaryKeyCommandLog* log = new AlterDropPrimaryKeyCommandLog();
	log->setCommand(new AlterDropPrimaryKeyCommand(*this));

	return log;
}


} /* namespace alinous */
