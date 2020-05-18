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
class ISchemaUptateListner;
class CdbTable;

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

	void createTable(CdbTable* table);

	const File* getDatabaseBaseDir() const noexcept {
		return databaseBaseDir;
	}

private:
	void fireSchemaLoaded() noexcept;
	void fireOnCreateTable(CdbTable* table);

private:
	SchemaRoot* root;
	File* schemaBin;
	File* databaseBaseDir;

	ArrayList<ISchemaUptateListner> listners;
};

} /* namespace alinous */

#endif /* SCHEMA_SCHEMAMANAGER_H_ */
