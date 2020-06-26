/*
 * ExtDomObject.h
 *
 *  Created on: 2020/06/25
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTDOMOBJECT_H_
#define EXT_BINARY_EXTDOMOBJECT_H_

#include "ext_binary/AbstractExtObject.h"

#include "base/HashMap.h"

namespace alinous {

class ExtDomObject : public AbstractExtObject {
public:
	explicit ExtDomObject(const UnicodeString* name);
	virtual ~ExtDomObject();

	void put(const UnicodeString* name, AbstractExtObject* value) noexcept;
	AbstractExtObject* get(const UnicodeString* name) const noexcept;
private:
	HashMap<UnicodeString, AbstractExtObject>* properties;
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTDOMOBJECT_H_ */
