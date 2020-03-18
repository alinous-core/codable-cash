/*
 * ExtStringClass.h
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTSTRINGCLASS_H_
#define EXT_BINARY_EXTSTRINGCLASS_H_

#include "ext_binary/AbstractExtObject.h"

namespace alinous {

class UnicodeString;

class ExtStringClass : public AbstractExtObject {
public:
	ExtStringClass(const UnicodeString* name, const UnicodeString* value);
	virtual ~ExtStringClass();

	const UnicodeString* getValue() const noexcept;
private:
	UnicodeString* value;
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTSTRINGCLASS_H_ */
