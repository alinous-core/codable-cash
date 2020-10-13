/*
 * ContinueStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_CONTINUESTATEMENT_H_
#define SC_STATEMENT_CTRL_CONTINUESTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {

class ContinueStatement: public AbstractStatement {
public:
	ContinueStatement();
	virtual ~ContinueStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);
	virtual bool hasCtrlStatement() const noexcept;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_CONTINUESTATEMENT_H_ */
