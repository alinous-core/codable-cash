/*
 * ClassDeclareBlock.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_DECLARE_CLASSDECLAREBLOCK_H_
#define SC_DECLARE_CLASSDECLAREBLOCK_H_

#include "engine/sc/CodeElement.h"
#include "base/ArrayList.h"

namespace alinous {

class MethodDeclare;
class MemberVariableDeclare;
class AnalyzeContext;
class VirtualMachine;
class UnicodeString;


class ClassDeclareBlock : public CodeElement{
public:
	ClassDeclareBlock();
	virtual ~ClassDeclareBlock();

	void preAnalyze(AnalyzeContext* actx);
	void addDefaultConstructor(const UnicodeString* className) noexcept;
	bool hasDefaultConstructor(const UnicodeString* className) const noexcept;
	void analyzeTypeRef(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void init(VirtualMachine* vm);

	void addMethod(MethodDeclare* method) noexcept;
	void addVariable(MemberVariableDeclare* variable) noexcept;
	ArrayList<MethodDeclare>* getMethods() noexcept;
	ArrayList<MemberVariableDeclare>* getMemberVariables() noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual bool hasCtrlStatement() const noexcept;
private:
	ArrayList<MethodDeclare> methods;
	ArrayList<MemberVariableDeclare> variables;
};

} /* namespace alinous */

#endif /* SC_DECLARE_CLASSDECLAREBLOCK_H_ */
