/*
 * AbstractExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ABSTRACTEXPRESSION_H_
#define SC_EXPRESSION_ABSTRACTEXPRESSION_H_

#include "sc/CodeElement.h"

namespace alinous {

class AnalyzeContext;

class AbstractExpression: public CodeElement {
public:
	explicit AbstractExpression(int kind);
	virtual ~AbstractExpression();

	virtual void preAnalyze(AnalyzeContext* actx) = 0;
	virtual void analyze(AnalyzeContext* actx) = 0;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ABSTRACTEXPRESSION_H_ */
