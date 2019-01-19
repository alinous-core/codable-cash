/*
 * LongType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_LONGTYPE_H_
#define SC_DECLARE_TYPES_LONGTYPE_H_

#include "sc_declare_types/AbstractPrimitiveType.h"

namespace alinous {

class LongType : public AbstractPrimitiveType {
public:
	LongType();
	virtual ~LongType();
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_LONGTYPE_H_ */
