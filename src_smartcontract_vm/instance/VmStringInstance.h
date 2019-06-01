/*
 * VmStringInstance.h
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#ifndef INSTANCE_VMSTRINGINSTANCE_H_
#define INSTANCE_VMSTRINGINSTANCE_H_

#include "instance/AbstractVmInstance.h"

namespace alinous {

class VmStringInstance : public AbstractVmInstance {
public:
	VmStringInstance();
	virtual ~VmStringInstance();
};

} /* namespace alinous */

#endif /* INSTANCE_VMSTRINGINSTANCE_H_ */
