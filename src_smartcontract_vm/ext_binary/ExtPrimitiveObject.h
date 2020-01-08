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
	explicit ExtPrimitiveObject(UnicodeString* name, uint8_t type);
	virtual ~ExtPrimitiveObject();

	static ExtPrimitiveObject* createBoolObject(UnicodeString* name, int8_t value) noexcept;
	static ExtPrimitiveObject* createByteObject(UnicodeString* name, int8_t value) noexcept;
	static ExtPrimitiveObject* createCharObject(UnicodeString* name, int16_t value) noexcept;
	static ExtPrimitiveObject* createShortObject(UnicodeString* name, int16_t value) noexcept;
	static ExtPrimitiveObject* createIntObject(UnicodeString* name, int32_t value) noexcept;
	static ExtPrimitiveObject* createLongObject(UnicodeString* name, int64_t value) noexcept;
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTPRIMITIVEOBJECT_H_ */
