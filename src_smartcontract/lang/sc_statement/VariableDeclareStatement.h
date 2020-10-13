/*
 * VariableDeclareStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_VARIABLEDECLARESTATEMENT_H_
#define SC_STATEMENT_VARIABLEDECLARESTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {
class AnalyzedType;
class AbstractType;
class VariableIdentifier;
class AbstractExpression;

class VariableDeclareStatement: public AbstractStatement {
public:
	VariableDeclareStatement();
	virtual ~VariableDeclareStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setType(AbstractType* type) noexcept;
	void setVariableId(VariableIdentifier* variable) noexcept;
	void setInitExpression(AbstractExpression* exp) noexcept;
	AnalyzedType getType() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void init(VirtualMachine* vm);
	virtual void interpret(VirtualMachine* vm);

	virtual bool hasCtrlStatement() const noexcept;

private:
	AbstractType* type;
	VariableIdentifier* variableId;
	AbstractExpression* exp;

	AnalyzedType* atype;
	bool bctrl;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_VARIABLEDECLARESTATEMENT_H_ */
