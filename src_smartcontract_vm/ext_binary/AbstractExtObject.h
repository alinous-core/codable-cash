/*
 * AbstractExtObject.h
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#ifndef EXT_BINARY_ABSTRACTEXTOBJECT_H_
#define EXT_BINARY_ABSTRACTEXTOBJECT_H_

namespace alinous {

class UnicodeString;

class AbstractExtObject {
public:
	explicit AbstractExtObject(UnicodeString* name);
	virtual ~AbstractExtObject();

protected:
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* EXT_BINARY_ABSTRACTEXTOBJECT_H_ */
