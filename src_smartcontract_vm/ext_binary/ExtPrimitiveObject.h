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
	explicit ExtPrimitiveObject(const UnicodeString* name, uint8_t type);
	virtual ~ExtPrimitiveObject();

	static ExtPrimitiveObject* createBoolObject(const UnicodeString* name, int8_t value) noexcept;
	static ExtPrimitiveObject* createByteObject(const UnicodeString* name, int8_t value) noexcept;
	static ExtPrimitiveObject* createCharObject(const UnicodeString* name, int16_t value) noexcept;
	static ExtPrimitiveObject* createShortObject(const UnicodeString* name, int16_t value) noexcept;
	static ExtPrimitiveObject* createIntObject(const UnicodeString* name, int32_t value) noexcept;
	static ExtPrimitiveObject* createLongObject(const UnicodeString* name, int64_t value) noexcept;

	int32_t getIntValue() const noexcept;
	void setIntValue(int32_t value) noexcept;

	bool getBoolValue() const noexcept;
	void setBoolValue(bool value) noexcept;

	int8_t getByteValue() const noexcept;
	void setByteValue(int8_t value) noexcept;
	int16_t getShortValue() const noexcept;
	void setShortValue(int16_t value) noexcept;
	int16_t getCharValue() const noexcept;
	void setCharValue(int16_t value) noexcept;
	int64_t getLongValue() const noexcept;
	void setLongValue(int64_t value) noexcept;

	virtual AbstractExtObject* copy() const noexcept;
private:
	uint8_t data[8];
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTPRIMITIVEOBJECT_H_ */
