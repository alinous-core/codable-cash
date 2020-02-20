/*
 * ExtArrayObject.h
 *
 *  Created on: 2020/02/18
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTARRAYOBJECT_H_
#define EXT_BINARY_EXTARRAYOBJECT_H_

#include "base/ArrayList.h"
#include "ext_binary/AbstractExtObject.h"

namespace alinous {

class AbstractExtObject;

class ExtArrayObject : public AbstractExtObject {
public:
	ExtArrayObject(const UnicodeString* name, int length);
	virtual ~ExtArrayObject();

	void addInnerElement(AbstractExtObject* obj) noexcept;
	int getLength() const noexcept;
	AbstractExtObject* get(int i) const noexcept;
private:
	ArrayList<AbstractExtObject> array;
	int length;
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTARRAYOBJECT_H_ */
