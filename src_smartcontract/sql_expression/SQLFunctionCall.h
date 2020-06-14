/*
 * SQLFunctionCall.h
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLFUNCTIONCALL_H_
#define SQL_EXPRESSION_SQLFUNCTIONCALL_H_

#include "sql/AbstractSQLExpression.h"
#include "base/ArrayList.h"

namespace alinous {
class VariableIdentifier;

class SQLFunctionCall : public AbstractSQLExpression {
public:
	SQLFunctionCall();
	virtual ~SQLFunctionCall();

	void setName(VariableIdentifier* name) noexcept;
	void addArgument(AbstractSQLExpression* arg) noexcept;

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
	VariableIdentifier* name;
	ArrayList<AbstractSQLExpression> arguments;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLFUNCTIONCALL_H_ */
