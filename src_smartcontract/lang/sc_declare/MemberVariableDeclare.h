/*
 * MemberVariableDeclare.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_DECLARE_MEMBERVARIABLEDECLARE_H_
#define SC_DECLARE_MEMBERVARIABLEDECLARE_H_

#include "engine/sc/CodeElement.h"

namespace alinous {

class AbstractType;
class AccessControlDeclare;
class UnicodeString;
class AnalyzeContext;
class AnalyzedType;
class VirtualMachine;
class AbstractExpression;
class AbstractReference;

class MemberVariableDeclare : public CodeElement {
public:
	MemberVariableDeclare();
	virtual ~MemberVariableDeclare();

	void preAnalyze(AnalyzeContext* actx);
	void analyzeTypeRef(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void init(VirtualMachine* vm);
	void onAllocate(VirtualMachine* vm, AbstractReference* ref);

	void setAccessControl(AccessControlDeclare* ctrl) noexcept;
	void setAccessControl(char ctrl) noexcept;
	void setType(AbstractType* type) noexcept;
	void setStatic(bool s) noexcept;
	void setName(UnicodeString* name) noexcept;

	bool isStatic() const noexcept;

	const UnicodeString* getName() noexcept;
	AbstractType* getType() noexcept;

	void setExp(AbstractExpression* exp) noexcept;
	AbstractExpression* getExp() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	AnalyzedType getAnalyzedType() const noexcept;

private:
	void doOnAllocate(VirtualMachine* vm, AbstractReference* ref);

private:
	AccessControlDeclare* ctrl;
	AbstractType* type;
	bool _static;
	UnicodeString* name;
	AbstractExpression* exp;

	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* SC_DECLARE_MEMBERVARIABLEDECLARE_H_ */
