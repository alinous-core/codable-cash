/*
 * MemberVariableAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_MEMBERVARIABLEACCESS_H_
#define VARIABLE_ACCESS_MEMBERVARIABLEACCESS_H_

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

class VariableIdentifier;

class MemberVariableAccess: public AbstractVariableInstraction {
public:
	MemberVariableAccess(VariableIdentifier* valId);
	virtual ~MemberVariableAccess();

private:
	VariableIdentifier* valId;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_MEMBERVARIABLEACCESS_H_ */
