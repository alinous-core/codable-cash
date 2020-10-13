/*
 * SQLBetweenExpression.h
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLBETWEENEXPRESSION_H_
#define SQL_EXPRESSION_SQLBETWEENEXPRESSION_H_

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

class SQLBetweenExpression : public AbstractSQLExpression {
public:
	SQLBetweenExpression();
	virtual ~SQLBetweenExpression();

	void setLeft(AbstractSQLExpression* exp) noexcept;
	void setStart(AbstractSQLExpression* exp) noexcept;
	void setEnd(AbstractSQLExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
	virtual void onSelectTarget(VirtualMachine* vm);
private:
	AbstractSQLExpression* left;
	AbstractSQLExpression* start;
	AbstractSQLExpression* end;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLBETWEENEXPRESSION_H_ */
