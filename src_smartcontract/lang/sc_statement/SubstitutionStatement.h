/*
 * SubstitutionStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_SUBSTITUTIONSTATEMENT_H_
#define SC_STATEMENT_SUBSTITUTIONSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {
class VariableIdentifier;
class AbstractExpression;

class SubstitutionStatement: public AbstractStatement {
public:
	SubstitutionStatement();
	virtual ~SubstitutionStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setVariableId(AbstractExpression* variable) noexcept;
	void setExpression(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	virtual bool hasCtrlStatement() const noexcept;
private:
	AbstractExpression* variable;
	AbstractExpression* exp;

	bool bctrl;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_SUBSTITUTIONSTATEMENT_H_ */
