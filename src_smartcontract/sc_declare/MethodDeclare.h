/*
 * MethodDeclare.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_DECLARE_METHODDECLARE_H_
#define SC_DECLARE_METHODDECLARE_H_

#include "sc/CodeElement.h"

namespace alinous {

class AccessControlDeclare;
class AbstractType;
class ArgumentsListDeclare;
class UnicodeString;
class StatementBlock;
class AnalyzeContext;
class AnalyzedType;

class MethodDeclare : public CodeElement {
public:
	MethodDeclare();
	virtual ~MethodDeclare();

	void preAnalyze(AnalyzeContext* actx);
	void analyzeTypeRef(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void setAccessControl(AccessControlDeclare* ctrl) noexcept;
	void setType(AbstractType* type) noexcept;
	void setStatic(bool s) noexcept;
	void setName(UnicodeString* name) noexcept;
	void setArguments(ArgumentsListDeclare* args) noexcept;
	void setBlock(StatementBlock* block) noexcept;

	bool isConstructor();
	const UnicodeString* getName() const noexcept;
	ArgumentsListDeclare* getArguments() const noexcept;
	AnalyzedType* getReturnedType() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AccessControlDeclare* ctrl;
	AbstractType* type;
	UnicodeString* name;
	bool _static;
	ArgumentsListDeclare* args;
	StatementBlock* block;

	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* SC_DECLARE_METHODDECLARE_H_ */
