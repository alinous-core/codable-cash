/*
 * AbstractType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_ABSTRACTTYPE_H_
#define SC_DECLARE_TYPES_ABSTRACTTYPE_H_

#include "sc/CodeElement.h"

namespace alinous {

class AbstractType : public CodeElement {
public:
	AbstractType(short kind);
	virtual ~AbstractType();

	virtual const UnicodeString* toString() noexcept = 0;
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_ABSTRACTTYPE_H_ */
