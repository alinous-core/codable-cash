/*
 * SubstitutionStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_SUBSTITUTIONSTATEMENT_H_
#define SC_STATEMENT_SUBSTITUTIONSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {
class VariableIdentifier;
class AbstractExpression;

class SubstitutionStatement: public AbstractStatement {
public:
	SubstitutionStatement();
	virtual ~SubstitutionStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setVariableId(VariableIdentifier* variable) noexcept;
	void setExpression(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	VariableIdentifier* variable;
	AbstractExpression* exp;

};

} /* namespace alinous */

#endif /* SC_STATEMENT_SUBSTITUTIONSTATEMENT_H_ */
