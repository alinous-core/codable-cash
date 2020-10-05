/*
 * TableRenameContext.h
 *
 *  Created on: 2020/10/05
 *      Author: iizuka
 */

#ifndef SCHEMA_ALTER_CTX_TABLERENAMECONTEXT_H_
#define SCHEMA_ALTER_CTX_TABLERENAMECONTEXT_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class CodableDatabase;
class CdbTable;
class AlterRenameTableCommandLog;
class SchemaManager;

class TableRenameContext {
public:
	TableRenameContext();
	virtual ~TableRenameContext();

	void init(const AlterRenameTableCommandLog* renameTableLog, SchemaManager* schemaManamger, const UnicodeString* defaultSchema);
	void validate(SchemaManager* schemaManamger);
	void commit(SchemaManager* schemaManamger);

	const CdbTable* getTable() const noexcept {
		return table;
	}

	bool isSchemaChanged() const noexcept;

	const UnicodeString* getDstSchema() const noexcept {
		return dstSchema;
	}

	const UnicodeString* getDstTable() const noexcept {
		return dstTable;
	}

private:
	UnicodeString* srcSchema;
	UnicodeString* dstSchema;

	UnicodeString* srcTable;
	UnicodeString* dstTable;

	CdbTable* table;
};

} /* namespace codablecash */

#endif /* SCHEMA_ALTER_CTX_TABLERENAMECONTEXT_H_ */
