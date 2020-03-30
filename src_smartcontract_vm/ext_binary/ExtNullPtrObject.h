/*
 * ExtNullPtrObject.h
 *
 *  Created on: 2020/03/28
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTNULLPTROBJECT_H_
#define EXT_BINARY_EXTNULLPTROBJECT_H_

#include "ext_binary/AbstractExtObject.h"

namespace alinous {

class ExtNullPtrObject : public AbstractExtObject {
public:
	ExtNullPtrObject(const UnicodeString* name, uint8_t type);
	virtual ~ExtNullPtrObject();

	virtual bool isNull() const noexcept;
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTNULLPTROBJECT_H_ */
