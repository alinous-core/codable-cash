/*
 * ObjectReference.h
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_OBJECTREFERENCE_H_
#define INSTANCE_REF_OBJECTREFERENCE_H_

#include "instance_ref/AbstractReference.h"

namespace alinous {

class ObjectReference : public AbstractReference {
public:
	explicit ObjectReference(uint8_t type);
	virtual ~ObjectReference();
};

} /* namespace alinous */

#endif /* INSTANCE_REF_OBJECTREFERENCE_H_ */
