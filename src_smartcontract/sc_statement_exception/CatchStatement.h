/*
 * CatchStatement.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_CATCHSTATEMENT_H_
#define SC_STATEMENT_CTRL_CATCHSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class StatementBlock;
class VariableDeclareStatement;

class CatchStatement : public AbstractStatement {
public:
	CatchStatement();
	virtual ~CatchStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	virtual bool hasCtrlStatement() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void setBlock(StatementBlock* block) noexcept;
	void setVariableDeclare(VariableDeclareStatement* variableDeclare) noexcept;

private:
	StatementBlock* block;
	VariableDeclareStatement* variableDeclare;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_CATCHSTATEMENT_H_ */
