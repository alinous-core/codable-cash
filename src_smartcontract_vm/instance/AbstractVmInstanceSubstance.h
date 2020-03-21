/*
 * AbstractVmInstanceSubstance.h
 *
 *  Created on: 2020/03/21
 *      Author: iizuka
 */

#ifndef INSTANCE_ABSTRACTVMINSTANCESUBSTANCE_H_
#define INSTANCE_ABSTRACTVMINSTANCESUBSTANCE_H_

#include "instance/AbstractVmInstance.h"

namespace alinous {

class AbstractVmInstanceSubstance : public AbstractVmInstance {
public:
	AbstractVmInstanceSubstance(uint8_t type);
	virtual ~AbstractVmInstanceSubstance();
};

} /* namespace alinous */

#endif /* INSTANCE_ABSTRACTVMINSTANCESUBSTANCE_H_ */
