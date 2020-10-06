/*
 * Schema.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMAMANAGER_H_
#define SCHEMA_SCHEMAMANAGER_H_
#include <cstdint>

#include "base/ArrayList.h"
#include "base/UnicodeString.h"

namespace alinous {
class UnicodeString;
class File;
class TableIdentifier;

}  // namespace alinous
using namespace alinous;

namespace codablecash {

class SchemaRoot;
class Schema;
class ISchemaUptateListner;
class CdbTable;
class AbstractAlterCommandLog;

class AlterAddColumnCommandLog;
class AlterAddIndexCommandLog;
class AlterDropIndexCommandLog;
class AlterAddPrimaryKeyCommandLog;
class AlterDropPrimaryKeyCommandLog;
class AlterDropColumnCommandLog;
class AlterModifyCommandLog;
class AlterRenameColumnCommandLog;
class AlterRenameTableCommandLog;
class ColumnModifyContext;
class CdbTableIndex;
class SchemaAlterCommandsHandler;
class CodableDatabase;
class TableRenameContext;

class SchemaManager {
public:
	friend class SchemaAlterCommandsHandler;

	static const UnicodeString PUBLIC;
	static const UnicodeString SCHEMA_FILE;

	explicit SchemaManager(CodableDatabase* db);
	virtual ~SchemaManager();

	void addSchemaUpdateListner(ISchemaUptateListner* listner) noexcept;

	static void createSchema(const UnicodeString* name, File* baseDir);

	void createSchema(const UnicodeString* name);

	void loadSchema(const File* baseDir);
	void save();

	uint64_t newTransactionId();
	uint64_t newSchemaObjectId() noexcept;
	uint64_t newRecordObjectId() noexcept;

	uint64_t getSchemaObjectVersionId() const noexcept;

	void createTable(CdbTable* table);

	Schema* getSchema(const UnicodeString* name) const noexcept;
	const ArrayList<Schema>* getSchemaList() const noexcept;

	CdbTable* getTable(const wchar_t* schema, const wchar_t* name) const;
	CdbTable* getTable(const UnicodeString* schema, const UnicodeString* name) const;
	CdbTable* getTable(const TableIdentifier* tableId, const UnicodeString* defaultSchema) const;

	//bool hasTable(const TableIdentifier* tableId) const noexcept;
	bool hasTable(const UnicodeString* schema, const UnicodeString* name) const noexcept;

	const File* getDatabaseBaseDir() const noexcept {
		return databaseBaseDir;
	}

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
	void fireSchemaLoaded() noexcept;
	void fireOnCreateTable(const CdbTable* table);
	void fireOnAlterModify(const CdbTable* table, const ColumnModifyContext* ctx);
	void fireOnDropPrimaryKey(const CdbTable* table, const CdbTableIndex* primaryKey);
	void fireOnAddPrimaryKey(const CdbTable* table, const CdbTableIndex* primaryKey);
	void fireOnRenameTable(const CdbTable* table, TableRenameContext* context);

	CdbTable* findTableFromCommand(const AbstractAlterCommandLog* cmdlog);

private:
	SchemaRoot* root;
	File* schemaBin;
	File* databaseBaseDir;

	SchemaAlterCommandsHandler* alterHandler;

	ArrayList<ISchemaUptateListner> listners;
};

} /* namespace alinous */

#endif /* SCHEMA_SCHEMAMANAGER_H_ */
