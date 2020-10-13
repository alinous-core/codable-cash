/*
 * SQLNullLiteral.h
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLNULLLITERAL_H_
#define SQL_EXPRESSION_SQLNULLLITERAL_H_

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {

class SQLNullLiteral : public AbstractSQLExpression {
public:
	SQLNullLiteral();
	virtual ~SQLNullLiteral();

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
	void interpretOnPlanning(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLNULLLITERAL_H_ */
