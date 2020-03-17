/*
 * ClassDeclare.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSDECLARE_H_
#define SC_DECLARE_CLASSDECLARE_H_

#include "sc/CodeElement.h"

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

class ClassDeclare : public CodeElement {
public:
	ClassDeclare();
	virtual ~ClassDeclare();

	void setInterface(bool interface) noexcept;

	void preAnalyze(AnalyzeContext* actx);
	void analyzeTypeRef(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void init(VirtualMachine* vm);

	void setBlock(ClassDeclareBlock* block) noexcept;
	void setName(UnicodeString* name) noexcept;
	void setExtends(ClassExtends* extends) noexcept;
	void setImplements(ClassImplements* implements) noexcept;

	const UnicodeString* getName() noexcept;
	const UnicodeString* getFullQualifiedName() noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	ClassDeclare* getBaseClass() const noexcept;
	int getInheritIndex() const noexcept;
	void setInheritIndex(int inheritIndex) noexcept;


	ArrayList<MethodDeclare>* getMethods() noexcept;
	ArrayList<MemberVariableDeclare>* getMemberVariables() noexcept;

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
