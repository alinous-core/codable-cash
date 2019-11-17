/*
 * NullArgument.h
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#ifndef EXT_ARGUMENTS_NULLARGUMENT_H_
#define EXT_ARGUMENTS_NULLARGUMENT_H_

#include "ext_arguments/AbstractFunctionExtArguments.h"

namespace alinous {

class NullArgument : public AbstractFunctionExtArguments {
public:
	NullArgument();
	virtual ~NullArgument();
};

} /* namespace alinous */

#endif /* EXT_ARGUMENTS_NULLARGUMENT_H_ */
