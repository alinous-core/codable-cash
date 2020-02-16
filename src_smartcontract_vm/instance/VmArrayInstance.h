/*
 * VmArrayInstance.h
 *
 *  Created on: 2020/02/16
 *      Author: iizuka
 */

#ifndef INSTANCE_VMARRAYINSTANCE_H_
#define INSTANCE_VMARRAYINSTANCE_H_
#include <cstdint>

#include "instance/IInstanceContainer.h"
#include "instance_parts/VMemList.h"

#include "instance/AbstractVmInstance.h"

namespace alinous {
class VirtualMachine;

class VmArrayInstance : public AbstractVmInstance, public IInstanceContainer {
public:
	VmArrayInstance(VirtualMachine* vm);
	virtual ~VmArrayInstance();

	virtual void removeInnerRefs(GcManager* gc) noexcept;

private:
	VMemList<AbstractReference>* array;
};

} /* namespace alinous */

#endif /* INSTANCE_VMARRAYINSTANCE_H_ */
