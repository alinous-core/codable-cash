/*
 * AbstractExtObject.h
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#ifndef EXT_BINARY_ABSTRACTEXTOBJECT_H_
#define EXT_BINARY_ABSTRACTEXTOBJECT_H_
#include <cstdint>

namespace alinous {

class UnicodeString;

class AbstractExtObject {
public:
	explicit AbstractExtObject(const UnicodeString* name, uint8_t type);
	virtual ~AbstractExtObject();

	const UnicodeString* getName() const noexcept;
	void setName(const UnicodeString* name) noexcept;
	uint8_t getType() const noexcept;

	virtual bool isNull() const noexcept;

	virtual AbstractExtObject* copy() const noexcept = 0;
protected:
	uint8_t type;
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* EXT_BINARY_ABSTRACTEXTOBJECT_H_ */
