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

class TableRenameContext {
public:
	TableRenameContext();
	virtual ~TableRenameContext();

	void init(const AlterRenameTableCommandLog* renameTableLog, CodableDatabase* db, const UnicodeString* defaultSchema);

private:
	UnicodeString* srcSchema;
	UnicodeString* dstSchema;

	UnicodeString* srcTable;
	UnicodeString* dstTable;

	CdbTable* table;
};

} /* namespace codablecash */

#endif /* SCHEMA_ALTER_CTX_TABLERENAMECONTEXT_H_ */
