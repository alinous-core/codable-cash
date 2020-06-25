/*
 * ExtDomObject.h
 *
 *  Created on: 2020/06/25
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTDOMOBJECT_H_
#define EXT_BINARY_EXTDOMOBJECT_H_

#include "ext_binary/AbstractExtObject.h"

namespace alinous {

class ExtDomObject : public AbstractExtObject {
public:
	explicit ExtDomObject(const UnicodeString* name);
	virtual ~ExtDomObject();
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTDOMOBJECT_H_ */
