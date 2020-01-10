/*
 * ExtClassObject.h
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTCLASSOBJECT_H_
#define EXT_BINARY_EXTCLASSOBJECT_H_

#include "ext_binary/AbstractExtObject.h"

#include "base/ArrayList.h"
#include "base/HashMap.h"

namespace alinous {

class UnicodeString;
class ExtPrimitiveObject;

class ExtClassObject : public AbstractExtObject {
public:
	explicit ExtClassObject(const UnicodeString* name);
	virtual ~ExtClassObject();

	void add(AbstractExtObject* obj) noexcept;
	ExtPrimitiveObject* getExtPrimitiveObject(UnicodeString* name) const noexcept;
private:
	ArrayList<AbstractExtObject>* list;
	HashMap<UnicodeString, AbstractExtObject>* map;
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTCLASSOBJECT_H_ */
