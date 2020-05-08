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

class IAbstractVmInstanceSubstance;
class GcCyclicCheckerContext;
class GcManager;

template <typename K, typename V> class HashMap;

class ReferenceStatus {
public:
	friend class ReferenceStatusCompare;

	explicit ReferenceStatus(IAbstractVmInstanceSubstance* instance);
	virtual ~ReferenceStatus();

	void addOwner(const IAbstractVmInstanceSubstance* owner) noexcept;
	void removeOwner(const IAbstractVmInstanceSubstance* owner) noexcept;
	bool isRemovable() const noexcept;

	void releseInnerRefs(GcManager* gc) noexcept;
	void deleteInstance() noexcept;

	IAbstractVmInstanceSubstance* getInstance() const noexcept;

	bool checkCyclicRemovable(GcCyclicCheckerContext* cctx, GcManager* gc) noexcept;

	int ownerSize() const noexcept;
private:
	IAbstractVmInstanceSubstance* instance;

	ArrayList<const IAbstractVmInstanceSubstance> ownerList;
	ArrayList<const IAbstractVmInstanceSubstance> terminalOwnerList;

};

} /* namespace alinous */

#endif /* INSTANCE_GC_REFERENCESTATUS_H_ */
