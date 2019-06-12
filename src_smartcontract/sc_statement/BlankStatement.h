/*
 * BlankStatement.h
 *
 *  Created on: 2019/02/15
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_BLANKSTATEMENT_H_
#define SC_STATEMENT_BLANKSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class BlankStatement : public AbstractStatement {
public:
	BlankStatement();
	virtual ~BlankStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SC_STATEMENT_BLANKSTATEMENT_H_ */
