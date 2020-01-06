/*
 * ExtClassObject.h
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#ifndef EXT_BINARY_EXTCLASSOBJECT_H_
#define EXT_BINARY_EXTCLASSOBJECT_H_

#include "ext_binary/AbstractExtObject.h"

namespace alinous {

class ExtClassObject : public AbstractExtObject {
public:
	ExtClassObject();
	virtual ~ExtClassObject();
};

} /* namespace alinous */

#endif /* EXT_BINARY_EXTCLASSOBJECT_H_ */
