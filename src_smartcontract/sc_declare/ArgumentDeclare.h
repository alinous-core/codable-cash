/*
 * ArgumentDeclare.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef SC_DECLARE_ARGUMENTDECLARE_H_
#define SC_DECLARE_ARGUMENTDECLARE_H_

#include "sc/CodeElement.h"

namespace alinous {

class AbstractType;
class UnicodeString;

class ArgumentDeclare : public CodeElement {
public:
	ArgumentDeclare();
	virtual ~ArgumentDeclare();

	void setType(AbstractType* type) noexcept;
	void setName(UnicodeString* name) noexcept;

private:
	AbstractType* type;
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* SC_DECLARE_ARGUMENTDECLARE_H_ */
