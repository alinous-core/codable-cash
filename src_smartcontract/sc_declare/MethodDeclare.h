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

class MethodDeclare : public CodeElement {
public:
	MethodDeclare();
	virtual ~MethodDeclare();

	void setAccessControl(AccessControlDeclare* ctrl) noexcept;
	void setType(AbstractType* type) noexcept;
	void setStatic(bool s) noexcept;
	void setName(UnicodeString* name) noexcept;
	void setArguments(ArgumentsListDeclare* args) noexcept;
	void setBlock(StatementBlock* block) noexcept;
private:
	AccessControlDeclare* ctrl;
	AbstractType* type;
	UnicodeString* name;
	bool _static;
	ArgumentsListDeclare* args;
	StatementBlock* block;
};

} /* namespace alinous */

#endif /* SC_DECLARE_METHODDECLARE_H_ */
