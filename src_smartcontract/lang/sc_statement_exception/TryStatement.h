/*
 * TryStatement.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_TRYSTATEMENT_H_
#define SC_STATEMENT_CTRL_TRYSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

#include "base/ArrayList.h"

namespace alinous {

class StatementBlock;
class CatchStatement;
class FinallyStatement;
class BlockState;

class TryStatement : public AbstractStatement {
public:
	TryStatement();
	virtual ~TryStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	virtual bool hasCtrlStatement() const noexcept;
	virtual bool hasConstructor() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void setBlock(StatementBlock* block) noexcept;
	void addCatchStatement(CatchStatement* catchStmt) noexcept;
	void setFinallyStatement(FinallyStatement* finallyStmt) noexcept;
private:
	StatementBlock* block;
	ArrayList<CatchStatement> catchStmts;
	FinallyStatement* finallyStmt;

	BlockState* blockState;
	bool bctrl;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_TRYSTATEMENT_H_ */
