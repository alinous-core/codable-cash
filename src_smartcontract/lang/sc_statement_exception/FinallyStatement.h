/*
 * FinallyStatement.h
 *
 *  Created on: 2020/04/15
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_EXCEPTION_FINALLYSTATEMENT_H_
#define SC_STATEMENT_EXCEPTION_FINALLYSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {

class StatementBlock;

class FinallyStatement : public AbstractStatement {
public:
	FinallyStatement();
	virtual ~FinallyStatement();

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

	virtual bool hasConstructor() const noexcept;
private:
	StatementBlock* block;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_EXCEPTION_FINALLYSTATEMENT_H_ */
