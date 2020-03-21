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
	VmArrayInstance(VirtualMachine* vm, int length);
	virtual ~VmArrayInstance();

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;

	virtual void removeInnerRefs(GcManager* gc) noexcept;
	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* reg);

	virtual int valueCompare(AbstractVmInstance* right);

	void setReference(VirtualMachine* vm, int pos, AbstractReference* ref) noexcept;
private:
	VMemList<AbstractReference>* array;
	int length;
};

} /* namespace alinous */

#endif /* INSTANCE_VMARRAYINSTANCE_H_ */
