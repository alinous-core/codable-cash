/*
 * AllocationExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ALLOCATIONEXPRESSION_H_
#define SC_EXPRESSION_ALLOCATIONEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {
class PackageNameDeclare;
class FunctionCallExpression;

class AllocationExpression : public AbstractExpression {
public:
	AllocationExpression();
	virtual ~AllocationExpression();

	void setPackage(PackageNameDeclare* packageName) noexcept;
	void setExpression(FunctionCallExpression* exp) noexcept;

private:
	PackageNameDeclare* packageName;
	FunctionCallExpression* exp;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ALLOCATIONEXPRESSION_H_ */
