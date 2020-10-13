/*
 * ThrowStatement.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_THROWSTATEMENT_H_
#define SC_STATEMENT_CTRL_THROWSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {

class AbstractExpression;

class ThrowStatement : public AbstractStatement {
public:
	ThrowStatement();
	virtual ~ThrowStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	virtual bool hasCtrlStatement() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void setExpression(AbstractExpression* exp) noexcept;

private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_THROWSTATEMENT_H_ */
