/*
 * SQLOrExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLOREXPRESSION_H_
#define SQL_EXPRESSION_SQLOREXPRESSION_H_

#include "lang_sql/sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

class SQLOrExpression : public AbstractSQLBinaryExpression {
public:
	SQLOrExpression();
	virtual ~SQLOrExpression();

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
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLOREXPRESSION_H_ */
