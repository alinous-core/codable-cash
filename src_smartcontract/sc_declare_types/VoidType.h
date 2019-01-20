/*
 * VoidType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_VOIDTYPE_H_
#define SC_DECLARE_TYPES_VOIDTYPE_H_

#include "sc_declare_types/AbstractType.h"

namespace alinous {

class VoidType : public AbstractType {
public:
	VoidType();
	virtual ~VoidType();
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_VOIDTYPE_H_ */
