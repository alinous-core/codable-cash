/*
 * AbstractPrimitiveType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_ABSTRACTPRIMITIVETYPE_H_
#define SC_DECLARE_TYPES_ABSTRACTPRIMITIVETYPE_H_

#include "sc/CodeElement.h"
#include "sc_declare/ITypeDeclare.h"

namespace alinous {

class AbstractPrimitiveType : public CodeElement, public ITypeDeclare {
public:
	AbstractPrimitiveType(short kind);
	virtual ~AbstractPrimitiveType();
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_ABSTRACTPRIMITIVETYPE_H_ */
