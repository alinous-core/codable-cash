/*
 * ReturnStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_RETURNSTATEMENT_H_
#define SC_STATEMENT_CTRL_RETURNSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {
class AbstractExpression;

class ReturnStatement: public AbstractStatement {
public:
	ReturnStatement();
	virtual ~ReturnStatement();

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
private:
	void interpretExpression(VirtualMachine* vm);
private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_RETURNSTATEMENT_H_ */
