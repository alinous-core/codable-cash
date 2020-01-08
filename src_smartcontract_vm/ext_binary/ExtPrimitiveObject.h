/*
 * ExtPrimitiveObject.h
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTPRIMITIVEOBJECT_H_
#define EXT_BINARY_EXTPRIMITIVEOBJECT_H_

#include "ext_binary/AbstractExtObject.h"

namespace alinous {

class ExtPrimitiveObject : public AbstractExtObject {
public:
	explicit ExtPrimitiveObject(UnicodeString* name);
	virtual ~ExtPrimitiveObject();
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTPRIMITIVEOBJECT_H_ */
