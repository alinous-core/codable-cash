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

class AnalyzedType;

class NullArgument : public AbstractFunctionExtArguments {
public:
	explicit NullArgument(const AnalyzedType* type);
	virtual ~NullArgument();

	virtual AnalyzedType getType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* EXT_ARGUMENTS_NULLARGUMENT_H_ */
