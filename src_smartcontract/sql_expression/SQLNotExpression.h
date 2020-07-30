/*
 * SQLNotExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLNOTEXPRESSION_H_
#define SQL_EXPRESSION_SQLNOTEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLNotExpression : public AbstractSQLExpression {
public:
	SQLNotExpression();
	virtual ~SQLNotExpression();

	void setExpression(AbstractSQLExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	void interpretOnPlanning(VirtualMachine* vm);
private:
	AbstractSQLExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLNOTEXPRESSION_H_ */
