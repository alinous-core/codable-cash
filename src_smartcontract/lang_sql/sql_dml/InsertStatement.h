/*
 * InsertStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_INSERTSTATEMENT_H_
#define SQL_DML_INSERTSTATEMENT_H_

#include "lang_sql/sql/AbstractSQLStatement.h"

namespace codablecash {
class CdbTableIdentifier;
class CdbTable;
}
using namespace codablecash;

namespace alinous {
class TableIdentifier;
class SQLColumnsList;
class SQLExpressionList;
class AnalyzedInsertColumnList;
class VmTransactionHandler;
class VirtualMachine;

class InsertStatement : public AbstractSQLStatement {
public:
	InsertStatement();
	virtual ~InsertStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setTable(TableIdentifier* tableId) noexcept;
	void setColumns(SQLColumnsList* columns) noexcept;
	void setExpressionList(SQLExpressionList* expList) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);
	void init(VirtualMachine* vm);

private:
	void updateSchemaInfo(VirtualMachine* vm, VmTransactionHandler* trxHandler);
	void updateSchemaInfoWithNoColumnSpec(CdbTable* table, VirtualMachine* vm, VmTransactionHandler* trxHandler);

private:
	TableIdentifier* tableId;
	SQLColumnsList* columns;
	SQLExpressionList* expList;

	uint64_t schemaVersion;
	AnalyzedInsertColumnList* analyzedColumns;
	CdbTableIdentifier* tableIdentifier;
};

} /* namespace alinous */

#endif /* SQL_DML_INSERTSTATEMENT_H_ */
