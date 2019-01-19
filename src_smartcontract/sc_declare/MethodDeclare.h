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

class UnicodeString;

class MethodDeclare : public CodeElement {
public:
	MethodDeclare();
	virtual ~MethodDeclare();

	void setStatic(bool s) noexcept;
	void setName(UnicodeString* name) noexcept;
private:
	UnicodeString* name;
	bool _static;
};

} /* namespace alinous */

#endif /* SC_DECLARE_METHODDECLARE_H_ */
