/*
 * IInstanceContainer.h
 *
 *  Created on: 2019/10/22
 *      Author: iizuka
 */

#ifndef INSTANCE_IINSTANCECONTAINER_H_
#define INSTANCE_IINSTANCECONTAINER_H_

#include "instance/IAbstractVmInstanceSubstance.h"

namespace alinous {

class GcManager;

class IInstanceContainer : public IAbstractVmInstanceSubstance{
public:
	IInstanceContainer();
	virtual ~IInstanceContainer();

	virtual void removeInnerRefs(GcManager* gc) noexcept = 0;
};

} /* namespace alinous */

#endif /* INSTANCE_IINSTANCECONTAINER_H_ */
