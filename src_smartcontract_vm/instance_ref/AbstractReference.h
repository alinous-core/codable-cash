/*
 * AbstractReference.h
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_ABSTRACTREFERENCE_H_
#define INSTANCE_REF_ABSTRACTREFERENCE_H_
#include <cstdint>

#include "instance/AbstractVmInstance.h"

namespace alinous {

class AbstractReference : public AbstractVmInstance {
public:
	AbstractReference(uint8_t type);
	virtual ~AbstractReference();
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ABSTRACTREFERENCE_H_ */
