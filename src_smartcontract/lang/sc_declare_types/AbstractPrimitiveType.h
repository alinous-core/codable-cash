/*
 * AbstractPrimitiveType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_ABSTRACTPRIMITIVETYPE_H_
#define SC_DECLARE_TYPES_ABSTRACTPRIMITIVETYPE_H_

#include "lang/sc_declare_types/AbstractType.h"

namespace alinous {

class AbstractPrimitiveType : public AbstractType {
public:
	explicit AbstractPrimitiveType(short kind);
	virtual ~AbstractPrimitiveType();
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_ABSTRACTPRIMITIVETYPE_H_ */
