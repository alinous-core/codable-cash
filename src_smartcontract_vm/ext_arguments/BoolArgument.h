/*
 * BoolArgument.h
 *
 *  Created on: 2020/03/19
 *      Author: iizuka
 */

#ifndef EXT_ARGUMENTS_BOOLARGUMENT_H_
#define EXT_ARGUMENTS_BOOLARGUMENT_H_

#include "ext_arguments/AbstractFunctionExtArguments.h"

namespace alinous {

class BoolArgument : public AbstractFunctionExtArguments {
public:
	explicit BoolArgument(bool value);
	virtual ~BoolArgument();

	virtual AnalyzedType getType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	bool value;
};

} /* namespace alinous */

#endif /* EXT_ARGUMENTS_BOOLARGUMENT_H_ */
