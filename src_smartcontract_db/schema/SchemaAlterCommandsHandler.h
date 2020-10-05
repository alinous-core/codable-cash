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
class CdbTable;
class ColumnModifyContext;
class AbstractAlterCommandLog;

class SchemaManager;
class CodableDatabase;

class SchemaAlterCommandsHandler {
public:
	explicit SchemaAlterCommandsHandler(CodableDatabase* db);
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

private:
	void handleUniqueIndexOnModify(CdbTable* table, ColumnModifyContext* ctx);
	void handleToNotUnique(CdbTable* table, ColumnModifyContext* ctx);
	void handleToUnique(CdbTable* table, ColumnModifyContext* ctx);

	CdbTable* findTableFromCommand(const AbstractAlterCommandLog* cmdlog);

private:
	SchemaManager* schemaManager;
	CodableDatabase* db;
};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMAALTERCOMMANDSHANDLER_H_ */
