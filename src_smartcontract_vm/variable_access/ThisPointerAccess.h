/*
 * ThisPointerAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_THISPOINTERACCESS_H_
#define VARIABLE_ACCESS_THISPOINTERACCESS_H_

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

class AnalyzedType;

class ThisPointerAccess: public AbstractVariableInstraction {
public:
	ThisPointerAccess();
	virtual ~ThisPointerAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst);

private:
	AnalyzedType* type;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_THISPOINTERACCESS_H_ */
