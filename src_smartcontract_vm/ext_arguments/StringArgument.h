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

class UnicodeString;

class StringArgument : public AbstractFunctionExtArguments {
public:
	explicit StringArgument(const UnicodeString* str);
	virtual ~StringArgument();

	virtual AnalyzedType getType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	UnicodeString* value;
};

} /* namespace alinous */

#endif /* EXT_ARGUMENTS_STRINGARGUMENT_H_ */
