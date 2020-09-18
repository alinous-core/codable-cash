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

namespace alinous {
class UnicodeString;
class File;

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

class SchemaManager {
public:
	static const UnicodeString PUBLIC;
	static const UnicodeString SCHEMA_FILE;

	SchemaManager();
	virtual ~SchemaManager();

	void addSchemaUpdateListner(ISchemaUptateListner* listner) noexcept;

	static void createSchema(const UnicodeString* name, File* baseDir);
	void loadSchema(const File* baseDir);
	void save();

	uint64_t newTransactionId();
	uint64_t newSchemaObjectId() noexcept;
	uint64_t newRecordObjectId() noexcept;

	uint64_t getSchemaObjectVersionId() const noexcept;

	void createTable(CdbTable* table);

	Schema* getSchema(const UnicodeString* name) const noexcept;
	CdbTable* getTable(const UnicodeString* schema, const UnicodeString* name) const;

	const File* getDatabaseBaseDir() const noexcept {
		return databaseBaseDir;
	}

	void handleAlterTableAddIndex(const AlterAddColumnCommandLog* cmd);
	void handleAlterTableAddColumn(const AlterAddIndexCommandLog* cmd);
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

private:
	SchemaRoot* root;
	File* schemaBin;
	File* databaseBaseDir;

	ArrayList<ISchemaUptateListner> listners;
};

} /* namespace alinous */

#endif /* SCHEMA_SCHEMAMANAGER_H_ */
