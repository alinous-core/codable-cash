/*
 * IfStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_IFSTATEMENT_H_
#define SC_STATEMENT_CTRL_IFSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

#include "base/ArrayList.h"

namespace alinous {

class AbstractExpression;

class IfStatement: public AbstractStatement {
public:
	IfStatement();
	virtual ~IfStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExpression(AbstractExpression* exp) noexcept;
	void setStatement(AbstractStatement* stmt) noexcept;

	void addElseIf(IfStatement* elseif) noexcept;
	void setElseStatement(AbstractStatement* elseStmt) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	virtual bool hasCtrlStatement() const noexcept;
	virtual bool hasConstructor() const noexcept;
private:
	AbstractExpression* exp;
	AbstractStatement* stmt;

	ArrayList<IfStatement> list;

	AbstractStatement* elseStmt;

	bool bctrl;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_IFSTATEMENT_H_ */
