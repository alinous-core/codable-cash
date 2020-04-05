/*
 * StatementBlock.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_STATEMENTBLOCK_H_
#define SC_STATEMENT_STATEMENTBLOCK_H_

#include "sc_statement/AbstractStatement.h"
#include "base/ArrayList.h"

namespace alinous {

class ArgumentsListDeclare;
class AnalyzeStack;
class BlockState;

class StatementBlock : public AbstractStatement {
public:
	StatementBlock();
	virtual ~StatementBlock();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void addStatement(AbstractStatement* stmt) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

private:
	void analyzeMethodDeclareBlock(AnalyzeContext* actx);
	void buildFunctionArguments2AnalyzedStack(ArgumentsListDeclare* arguments, AnalyzeStack* stack) const;
	void interpretFunctionArguments(VirtualMachine* vm);
private:
	ArrayList<AbstractStatement> statements;
	BlockState* blockState;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_STATEMENTBLOCK_H_ */
