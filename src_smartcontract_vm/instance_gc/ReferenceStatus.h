/*
 * ReferenceStatus.h
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_REFERENCESTATUS_H_
#define INSTANCE_GC_REFERENCESTATUS_H_

#include "base/ArrayList.h"

namespace alinous {

class AbstractVmInstance;
class GcCyclicCheckerContext;
class GcManager;

template <typename K, typename V> class HashMap;

class ReferenceStatus {
public:
	friend class ReferenceStatusCompare;

	explicit ReferenceStatus(AbstractVmInstance* instance);
	virtual ~ReferenceStatus();

	void addOwner(const AbstractVmInstance* owner) noexcept;
	void removeOwner(const AbstractVmInstance* owner) noexcept;
	bool isRemovable() const noexcept;

	void releseInnerRefs(GcManager* gc) noexcept;
	void deleteInstance() noexcept;

	AbstractVmInstance* getInstance() const noexcept;

	void removeInstance() noexcept;
	bool checkCyclicRemovable(GcCyclicCheckerContext* cctx) noexcept;
	bool checkInnerCyclicRemovable(const AbstractVmInstance* inst, GcCyclicCheckerContext* cctx) const noexcept;

private:
	AbstractVmInstance* instance;

	ArrayList<const AbstractVmInstance> ownerList;
	ArrayList<const AbstractVmInstance> terminalOwnerList;

};

} /* namespace alinous */

#endif /* INSTANCE_GC_REFERENCESTATUS_H_ */
