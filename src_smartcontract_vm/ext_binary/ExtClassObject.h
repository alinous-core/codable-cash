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
class ExtArrayObject;
class ExtStringClass;
class ExtExceptionObject;
class ExtDomObject;

class ExtClassObject : public AbstractExtObject {
public:
	explicit ExtClassObject(const UnicodeString* name);
	virtual ~ExtClassObject();

	void add(AbstractExtObject* obj) noexcept;
	ExtPrimitiveObject* getExtPrimitiveObject(const UnicodeString* name) const noexcept;
	ExtClassObject* getExtClassObject(const UnicodeString* name) const noexcept;
	ExtArrayObject* getExtArrayObject(const UnicodeString* name) const noexcept;
	ExtStringClass* getExtStringObject(const UnicodeString* name)const noexcept;
	ExtExceptionObject* getExtExceptionObject(const UnicodeString* name)const noexcept;
	ExtDomObject* getExtDomObject(const UnicodeString* name) const noexcept;

	virtual AbstractExtObject* copy() const noexcept;
private:
	ArrayList<AbstractExtObject>* list;
	HashMap<UnicodeString, AbstractExtObject>* map;
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTCLASSOBJECT_H_ */
