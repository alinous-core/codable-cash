/*
 * TryStatement.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_TRYSTATEMENT_H_
#define SC_STATEMENT_CTRL_TRYSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

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


	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_TRYSTATEMENT_H_ */
