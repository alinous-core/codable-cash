/*
 * VoidType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_VOIDTYPE_H_
#define SC_DECLARE_TYPES_VOIDTYPE_H_

#include "sc_declare/ITypeDeclare.h"
#include "sc/CodeElement.h"

namespace alinous {

class VoidType : public CodeElement, public ITypeDeclare {
public:
	VoidType();
	virtual ~VoidType();
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_VOIDTYPE_H_ */
