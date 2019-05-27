/*
 * ArrayInstance.h
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#ifndef INSTANCE_VMARRAYINSTANCE_H_
#define INSTANCE_VMARRAYINSTANCE_H_

#include "instance/AbstractVmInstance.h"

namespace alinous {

class VmArrayInstance : public AbstractVmInstance {
public:
	VmArrayInstance();
	virtual ~VmArrayInstance();
};

} /* namespace alinous */

#endif /* INSTANCE_VMARRAYINSTANCE_H_ */
