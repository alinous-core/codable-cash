/*
 * DoWhileStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_DOWHILESTATEMENT_H_
#define SC_STATEMENT_CTRL_DOWHILESTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {
class AbstractExpression;

class DoWhileStatement: public AbstractStatement {
public:
	DoWhileStatement();
	virtual ~DoWhileStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExpression(AbstractExpression* exp) noexcept;
	void setStatement(AbstractStatement* stmt) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);
private:
	AbstractExpression* exp;
	AbstractStatement* stmt;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_DOWHILESTATEMENT_H_ */
