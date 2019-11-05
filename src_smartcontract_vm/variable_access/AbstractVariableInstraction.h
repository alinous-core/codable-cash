/*
 * AbstractVariableInstraction.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_
#define VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_

namespace alinous {

class AnalyzeContext;

class AbstractVariableInstraction {
public:
	AbstractVariableInstraction();
	virtual ~AbstractVariableInstraction();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst) = 0;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_ */
