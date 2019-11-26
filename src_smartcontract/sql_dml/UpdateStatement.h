/*
 * UpdateStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_UPDATESTATEMENT_H_
#define SQL_DML_UPDATESTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {
class TableIdentifier;
class SQLSet;
class SQLWhere;

class UpdateStatement : public AbstractSQLStatement {
public:
	UpdateStatement();
	virtual ~UpdateStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setTable(TableIdentifier* tableId) noexcept;
	void setSet(SQLSet* set) noexcept;
	void setWhere(SQLWhere* where) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);
private:
	TableIdentifier* tableId;
	SQLSet* set;
	SQLWhere* where;
};

} /* namespace alinous */

#endif /* SQL_DML_UPDATESTATEMENT_H_ */
