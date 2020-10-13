/*
 * SelectStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_SELECTSTATEMENT_H_
#define SQL_DML_SELECTSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"
#include <cstdint>

namespace codablecash {
class SelectScanPlanner;
}
using namespace codablecash;

namespace alinous {
class SQLSelectTargetList;
class SQLFrom;
class SQLWhere;
class SQLGroupBy;
class SQLOrderBy;
class SQLLimitOffset;

class SelectStatement : public AbstractSQLStatement {
public:
	SelectStatement();
	virtual ~SelectStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setList(SQLSelectTargetList* list) noexcept;
	void setFrom(SQLFrom* from) noexcept;
	void setWhere(SQLWhere* where) noexcept;
	void setGroupBy(SQLGroupBy* groupBy) noexcept;
	void setOrderBy(SQLOrderBy* orderBy) noexcept;
	void setLimitOffset(SQLLimitOffset* limitOffset) noexcept;

	void setintoVar(UnicodeString* intoVar) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	SQLSelectTargetList* getSQLSelectTargetList() const noexcept;
private:
	void buildPlanner(VirtualMachine* vm, uint64_t currentVer);

private:
	SQLSelectTargetList* list;
	SQLFrom* from;
	SQLWhere* where;
	SQLGroupBy* groupBy;
	SQLOrderBy* orderBy;
	SQLLimitOffset* limitOffset;

	UnicodeString* intoVar;

	uint64_t lastSchemaVersion;
	SelectScanPlanner* planner;
};

} /* namespace alinous */

#endif /* SQL_DML_SELECTSTATEMENT_H_ */
