/*
 * CharType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_CHARTYPE_H_
#define SC_DECLARE_TYPES_CHARTYPE_H_

#include "sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {

class CharType : public AbstractPrimitiveType {
public:
	CharType();
	virtual ~CharType();
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_CHARTYPE_H_ */
