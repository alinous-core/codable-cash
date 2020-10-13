/*
 * MemberVariableAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_MEMBERVARIABLEACCESS_H_
#define VARIABLE_ACCESS_MEMBERVARIABLEACCESS_H_

#include "vm/variable_access/AbstractVariableInstraction.h"

namespace alinous {

class VariableIdentifier;
class AnalyzedType;
class StaticVariableMetadata;

class MemberVariableAccess: public AbstractVariableInstraction {
public:
	explicit MemberVariableAccess(VariableIdentifier* valId);
	virtual ~MemberVariableAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);
	virtual AnalyzedType getAnalyzedType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst);
	virtual bool hasErrorOnAnalyze() const noexcept;

	virtual CodeElement* getCodeElement() const noexcept;

private:
	void analyzeStaticWithClassType(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst);
	AbstractVmInstance* interpretStaticWithClassType(VirtualMachine* vm, AbstractVmInstance* lastInst);
	void analyzeDomType(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst);
	AbstractVmInstance* interpretDomType(VirtualMachine* vm, AbstractVmInstance* lastInst);
	AbstractVmInstance* interpretDomArrayType(VirtualMachine* vm, AbstractVmInstance* lastInst);
private:
	VariableIdentifier* valId;
	int memberIndex;
	StaticVariableMetadata* meta;
	AnalyzedType* atype;

	CodeElement* element;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_MEMBERVARIABLEACCESS_H_ */
