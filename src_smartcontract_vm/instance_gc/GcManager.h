/*
 * GcManager.h
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_GCMANAGER_H_
#define INSTANCE_GC_GCMANAGER_H_

namespace alinous {

class AbstractVmInstance;

class GcManager {
public:
	GcManager();
	virtual ~GcManager();

	void addReference(AbstractVmInstance* owner, AbstractVmInstance* refered) noexcept;
	void removeReference(AbstractVmInstance* owner, AbstractVmInstance* refered) noexcept;

private:
	AbstractVmInstance* mainInst;

};

} /* namespace alinous */

#endif /* INSTANCE_GC_GCMANAGER_H_ */
