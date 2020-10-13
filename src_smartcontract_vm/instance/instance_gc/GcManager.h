/*
 * GcManager.h
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_GCMANAGER_H_
#define INSTANCE_GC_GCMANAGER_H_

#include "base/HashMap.h"
#include "instance/instance_gc/ReferenceStatusCompare.h"

namespace alinous {

class AbstractVmInstance;
class ReferenceStatus;
class VmInstanceKey;
class AbstractReference;
class GcCyclicCheckerContext;
class ReferenceStatusCompare;
class IAbstractVmInstanceSubstance;

class GcManager {
public:
	GcManager();
	virtual ~GcManager();

	void registerObject(AbstractReference* ref);
	void removeObject(AbstractReference* ref);

	void handleFloatingObject(IAbstractVmInstanceSubstance* refered) noexcept;

	ReferenceStatus* getReferenceStatus(const IAbstractVmInstanceSubstance* ref) const noexcept;

	void garbageCollect();
	bool isEmpty() const noexcept;
private:
	void addToRemoveble(ReferenceStatus* status) noexcept;
	void addToNeedCheck(ReferenceStatus* status) noexcept;
	void removeFromNeedCheck(ReferenceStatus* status) noexcept;
	void removeFromRemoveble(ReferenceStatus* status) noexcept;

	void checkCycric() noexcept;
	void removeGcCyclicCheckerContext(GcCyclicCheckerContext* cctx) noexcept;
	void copyAll(HashMap<VmInstanceKey, ReferenceStatus>* checkHash) noexcept;

private:
	HashMap<VmInstanceKey, ReferenceStatus> statuses;
	HashMap<VmInstanceKey, ReferenceStatus> needCheck;

	ArrayList<ReferenceStatus, ReferenceStatusCompare> removable;

};

} /* namespace alinous */

#endif /* INSTANCE_GC_GCMANAGER_H_ */
