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
	explicit AbstractReference(IAbstractVmInstanceSubstance* owner, uint8_t type);
	virtual ~AbstractReference();

	virtual bool isPrimitive() const noexcept;
	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;
	virtual bool isReference() const noexcept;

	virtual void substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm);

	IAbstractVmInstanceSubstance* getOwner() const noexcept;
protected:
	IAbstractVmInstanceSubstance* const owner;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_ABSTRACTREFERENCE_H_ */
