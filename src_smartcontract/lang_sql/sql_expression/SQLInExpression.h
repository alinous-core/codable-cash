/*
 * SQLInExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLINEXPRESSION_H_
#define SQL_EXPRESSION_SQLINEXPRESSION_H_

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {
class SQLExpressionList;

class SQLInExpression : public AbstractSQLExpression {
public:
	SQLInExpression();
	virtual ~SQLInExpression();

	void setLeft(AbstractSQLExpression* left) noexcept;
	void setList(SQLExpressionList* list) noexcept;

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
	SQLExpressionList* list;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLINEXPRESSION_H_ */
