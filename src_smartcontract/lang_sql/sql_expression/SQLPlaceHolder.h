/*
 * SQLPlaceHolder.h
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLPLACEHOLDER_H_
#define SQL_EXPRESSION_SQLPLACEHOLDER_H_

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

class AbstractExpression;

class SQLPlaceHolder : public AbstractSQLExpression {
public:
	SQLPlaceHolder();
	virtual ~SQLPlaceHolder();

	void setExpression(AbstractExpression* exp) noexcept;

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
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLPLACEHOLDER_H_ */
