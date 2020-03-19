/*
 * NumericArgument.h
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#ifndef EXT_ARGUMENTS_NUMERICARGUMENT_H_
#define EXT_ARGUMENTS_NUMERICARGUMENT_H_

#include "ext_arguments/AbstractFunctionExtArguments.h"

namespace alinous {

class NumericArgument : public AbstractFunctionExtArguments {
public:
	NumericArgument();
	virtual ~NumericArgument();

	virtual AnalyzedType getType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* EXT_ARGUMENTS_NUMERICARGUMENT_H_ */
