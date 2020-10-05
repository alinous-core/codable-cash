/*
 * SchemaAlterCommandsHandler.h
 *
 *  Created on: 2020/10/05
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMAALTERCOMMANDSHANDLER_H_
#define SCHEMA_SCHEMAALTERCOMMANDSHANDLER_H_

namespace codablecash {

class AlterAddIndexCommandLog;
class AlterAddColumnCommandLog;
class AlterDropIndexCommandLog;
class AlterDropColumnCommandLog;
class AlterAddPrimaryKeyCommandLog;
class AlterDropPrimaryKeyCommandLog;
class AlterModifyCommandLog;
class AlterRenameColumnCommandLog;
class AlterRenameTableCommandLog;

class SchemaAlterCommandsHandler {
public:
	SchemaAlterCommandsHandler();
	virtual ~SchemaAlterCommandsHandler();

	void handleAlterTableAddIndex(const AlterAddIndexCommandLog* cmd);
	void handleAlterTableAddColumn(const AlterAddColumnCommandLog* cmd);
	void handleAlterTableDropIndex(const AlterDropIndexCommandLog* cmd);
	void handleAlterTableDropColumn(const AlterDropColumnCommandLog* cmd);
	void handleAlterTableAddPrimaryKey(const AlterAddPrimaryKeyCommandLog* cmd);
	void handleAlterTableDropPrimaryKey(const AlterDropPrimaryKeyCommandLog* cmd);
	void handleAlterTableModify(const AlterModifyCommandLog* cmd);
	void handleAlterTableRenameColumn(const AlterRenameColumnCommandLog* cmd);
	void handleAlterTableRenameTable(const AlterRenameTableCommandLog* cmd);
};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMAALTERCOMMANDSHANDLER_H_ */
