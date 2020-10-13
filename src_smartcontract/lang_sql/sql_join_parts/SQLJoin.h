/*
 * SQLJoin.h
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLJOIN_H_
#define SQL_DML_PARTS_SQLJOIN_H_

#include "lang_sql/sql/AbstractJoinPart.h"
#include <cstdint>

#include "base/ArrayList.h"

namespace codablecash {
class AbstractJoinScanTarget;
class AbstractScanTableTarget;
class SelectScanPlanner;
}
using namespace codablecash;

namespace alinous {

class AbstractSQLExpression;
class SQLJoinPart;

class SQLJoin : public AbstractJoinPart {
public:
	SQLJoin();
	virtual ~SQLJoin();

	void setFirst(AbstractJoinPart* first) noexcept;
	void addJoinPart(SQLJoinPart* part) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

	static AbstractJoinScanTarget* newScanTarget(uint8_t joinType);

private:
	void handleOnCondition(VirtualMachine* vm, SelectScanPlanner* planner, AbstractJoinScanTarget* currentJoin, AbstractSQLExpression* exp);

private:
	AbstractJoinPart* first;
	ArrayList<SQLJoinPart> list;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLJOIN_H_ */
