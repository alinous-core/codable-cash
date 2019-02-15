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

	void setVariableId(VariableIdentifier* variable) noexcept;
	void setExpression(AbstractExpression* exp) noexcept;
private:
	VariableIdentifier* variable;
	AbstractExpression* exp;

};

} /* namespace alinous */

#endif /* SC_STATEMENT_SUBSTITUTIONSTATEMENT_H_ */
