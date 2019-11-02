/*
 * StackVariableAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_STACKVARIABLEACCESS_H_
#define VARIABLE_ACCESS_STACKVARIABLEACCESS_H_

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

class StackVariableAccess: public AbstractVariableInstraction {
public:
	StackVariableAccess(int stackPos, int pos);
	virtual ~StackVariableAccess();

private:
	int stackPos;
	int pos;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_STACKVARIABLEACCESS_H_ */
