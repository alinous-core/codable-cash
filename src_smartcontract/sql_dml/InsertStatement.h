/*
 * InsertStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_INSERTSTATEMENT_H_
#define SQL_DML_INSERTSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {
class TableIdentifier;
class SQLColumnsList;
class SQLExpressionList;

class InsertStatement : public AbstractSQLStatement {
public:
	InsertStatement();
	virtual ~InsertStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setTable(TableIdentifier* tableId) noexcept;
	void setColumns(SQLColumnsList* columns) noexcept;
	void setExpressionList(SQLExpressionList* expList) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);
private:
	TableIdentifier* tableId;
	SQLColumnsList* columns;
	SQLExpressionList* expList;
};

} /* namespace alinous */

#endif /* SQL_DML_INSERTSTATEMENT_H_ */
