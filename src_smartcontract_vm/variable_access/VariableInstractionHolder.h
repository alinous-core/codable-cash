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

class VariableInstractionHolder {
public:
	VariableInstractionHolder();
	virtual ~VariableInstractionHolder();

	void addExpression(AbstractExpression* exp, AnalyzeContext* actx) noexcept;

private:
	void addVariableIdExp(AbstractExpression* exp, AnalyzeContext* actx) noexcept;
	void addArrayReference(AbstractExpression* exp, AnalyzeContext* actx) noexcept;

private:
	ArrayList<AbstractVariableInstraction> list;
	bool memberAccess;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_VARIABLEINSTRACTIONHOLDER_H_ */
