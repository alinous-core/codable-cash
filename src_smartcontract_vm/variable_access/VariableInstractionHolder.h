/*
 * VariableInstractionHolder.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_VARIABLEINSTRACTIONHOLDER_H_
#define VARIABLE_ACCESS_VARIABLEINSTRACTIONHOLDER_H_

#include "base/ArrayList.h"

namespace alinous {

class AbstractVariableInstraction;
class AbstractExpression;
class AnalyzeContext;
class VariableIdentifier;
class AbstractVmInstance;
class VirtualMachine;
class AnalyzedType;
class CodeElement;
class StackVariableAccess;

class VariableInstractionHolder {
public:
	VariableInstractionHolder();
	virtual ~VariableInstractionHolder();

	void addFirstClassIdentifier(const AnalyzedType* atp) noexcept;
	void addExpression(AbstractExpression* exp, AnalyzeContext* actx) noexcept;
	void analyze(AnalyzeContext* actx, CodeElement* element);
	AnalyzedType* getAnalyzedType() const noexcept;
	AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	AbstractVariableInstraction* detectNonStackInstruction(VariableIdentifier* valId, AnalyzeContext* actx) noexcept;
	AbstractVariableInstraction* handleSuper(VariableIdentifier* valId, AnalyzeContext* actx) noexcept;
	void addVariableIdExp(AbstractExpression* exp, AnalyzeContext* actx) noexcept;
	AbstractVariableInstraction* doAddVariableIdExp(AbstractExpression* exp, AnalyzeContext* actx) noexcept;
	StackVariableAccess* handleStackVariableIdExp(VariableIdentifier* valId, AbstractExpression* exp, AnalyzeContext* actx) noexcept;
	void addArrayReference(AbstractExpression* exp, AnalyzeContext* actx) noexcept;
	void addFunctionCallExp(AbstractExpression* exp, AnalyzeContext* actx) noexcept;

	bool checkNotVoid(AnalyzeContext* actx, AbstractVariableInstraction* inst);
private:
	ArrayList<AbstractVariableInstraction> list;
	bool memberAccess;
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_VARIABLEINSTRACTIONHOLDER_H_ */
