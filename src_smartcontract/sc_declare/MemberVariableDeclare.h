/*
 * MemberVariableDeclare.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_DECLARE_MEMBERVARIABLEDECLARE_H_
#define SC_DECLARE_MEMBERVARIABLEDECLARE_H_

#include "sc/CodeElement.h"

namespace alinous {

class AbstractType;
class AccessControlDeclare;
class UnicodeString;

class MemberVariableDeclare : public CodeElement {
public:
	MemberVariableDeclare();
	virtual ~MemberVariableDeclare();

	void setAccessControl(AccessControlDeclare* ctrl) noexcept;
	void setType(AbstractType* type) noexcept;
	void setStatic(bool s) noexcept;
	void setName(UnicodeString* name) noexcept;
private:
	AccessControlDeclare* ctrl;
	AbstractType* type;
	bool _static;
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* SC_DECLARE_MEMBERVARIABLEDECLARE_H_ */
