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
class AnalyzedType;

class MemberVariableAccess: public AbstractVariableInstraction {
public:
	MemberVariableAccess(VariableIdentifier* valId);
	virtual ~MemberVariableAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst);
	virtual AnalyzedType* getAnalyzedType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst);
private:
	VariableIdentifier* valId;
	int memberIndex;
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_MEMBERVARIABLEACCESS_H_ */
