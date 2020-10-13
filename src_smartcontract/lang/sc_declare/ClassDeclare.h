/*
 * ClassDeclare.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSDECLARE_H_
#define SC_DECLARE_CLASSDECLARE_H_

#include "engine/sc/CodeElement.h"

#include "base/ArrayList.h"

namespace alinous {

class ClassDeclareBlock;
class UnicodeString;
class AnalyzeContext;
class ClassExtends;
class ClassImplements;
class VirtualMachine;
class AnalyzedType;
class MethodDeclare;
class MemberVariableDeclare;
class AnalyzedClass;
class VTableRegistory;
class VTableClassEntry;
class IVmInstanceFactory;

class ClassDeclare : public CodeElement {
public:
	ClassDeclare();
	virtual ~ClassDeclare();

	void setInterface(bool interface) noexcept;
	bool isInterface() const noexcept;

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void init(VirtualMachine* vm);

	void setBlock(ClassDeclareBlock* block) noexcept;
	void setName(UnicodeString* name) noexcept;
	void setExtends(ClassExtends* extends) noexcept;
	void setImplements(ClassImplements* implements) noexcept;

	ClassExtends* getExtends() const noexcept;

	virtual const UnicodeString* getName() noexcept;
	virtual const UnicodeString* getFullQualifiedName() noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual ClassDeclare* getBaseClass() const noexcept;
	int getInheritIndex() const noexcept;
	void setInheritIndex(int inheritIndex) noexcept;


	virtual ArrayList<MethodDeclare>* getMethods() noexcept;
	virtual ArrayList<MemberVariableDeclare>* getMemberVariables() noexcept;

	virtual IVmInstanceFactory* getFactory() const noexcept;

private:
	void checkImplementsInterfaces(AnalyzeContext* actx);
	void checkImplementsInterface(AnalyzeContext* actx, AnalyzedClass* aclass, VTableRegistory* vreg, VTableClassEntry* thisEntry);
	bool isImplemented(VTableClassEntry* thisEntry, MethodDeclare* method);
	void addDefaultConstructor() noexcept;

protected:
	bool interface;
	ClassDeclareBlock* block;
	UnicodeString* name;
	ClassExtends* extends;
	ClassImplements* implements;

	int inheritIndex;
	UnicodeString* fqn;
};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSDECLARE_H_ */
