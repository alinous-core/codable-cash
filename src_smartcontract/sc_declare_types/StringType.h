/*
 * StringType.h
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#ifndef SC_DECLARE_TYPES_STRINGTYPE_H_
#define SC_DECLARE_TYPES_STRINGTYPE_H_

#include "sc_declare_types/AbstractType.h"

namespace alinous {

class StringType : public AbstractType {
public:
	StringType();
	virtual ~StringType();
};

} /* namespace alinous */

#endif /* SC_DECLARE_TYPES_STRINGTYPE_H_ */
