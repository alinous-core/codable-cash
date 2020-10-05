/*
 * SchemaAlterCommandsHandler.cpp
 *
 *  Created on: 2020/10/05
 *      Author: iizuka
 */

#include "schema/SchemaAlterCommandsHandler.h"

#include "transaction_log_alter/AlterAddIndexCommandLog.h"
#include "transaction_log_alter/AlterAddColumnCommandLog.h"

#include "transaction_log_alter/AlterDropIndexCommandLog.h"

#include "transaction_log_alter/AlterDropColumnCommandLog.h"

#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"

#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"
namespace codablecash {

SchemaAlterCommandsHandler::SchemaAlterCommandsHandler() {
	// TODO Auto-generated constructor stub

}

SchemaAlterCommandsHandler::~SchemaAlterCommandsHandler() {
	// TODO Auto-generated destructor stub
}

void SchemaAlterCommandsHandler::handleAlterTableAddIndex(const AlterAddIndexCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableAddColumn(const AlterAddColumnCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableDropIndex(const AlterDropIndexCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableDropColumn(const AlterDropColumnCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableAddPrimaryKey(const AlterAddPrimaryKeyCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableDropPrimaryKey(const AlterDropPrimaryKeyCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableModify(const AlterModifyCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableRenameColumn(const AlterRenameColumnCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableRenameTable(const AlterRenameTableCommandLog* cmd) {
}

} /* namespace codablecash */
