/*
 * StringArgument.h
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#ifndef EXT_ARGUMENTS_STRINGARGUMENT_H_
#define EXT_ARGUMENTS_STRINGARGUMENT_H_

#include "ext_arguments/AbstractFunctionExtArguments.h"

namespace alinous {

class StringArgument : public AbstractFunctionExtArguments {
public:
	StringArgument();
	virtual ~StringArgument();
};

} /* namespace alinous */

#endif /* EXT_ARGUMENTS_STRINGARGUMENT_H_ */
