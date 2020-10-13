/*
 * ExpressionStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_EXPRESSIONSTATEMENT_H_
#define SC_STATEMENT_EXPRESSIONSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {
class AbstractExpression;

class ExpressionStatement : public AbstractStatement {
public:
	ExpressionStatement();
	virtual ~ExpressionStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExpression(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	virtual bool hasCtrlStatement() const noexcept;
	virtual bool hasConstructor() const noexcept;
private:
	AbstractExpression* exp;

	bool bctrl;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_EXPRESSIONSTATEMENT_H_ */
