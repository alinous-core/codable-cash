/*
 * GcCyclicCheckerContext.h
 *
 *  Created on: 2019/07/17
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_GCCYCLICCHECKERCONTEXT_H_
#define INSTANCE_GC_GCCYCLICCHECKERCONTEXT_H_
#include "base/ArrayList.h"

namespace alinous {

class ReferenceStatus;
class GcManager;

class GcCyclicCheckerContext {
public:
	explicit GcCyclicCheckerContext(GcManager* gc);
	virtual ~GcCyclicCheckerContext();

	void addInstance(ReferenceStatus* inst) noexcept;
	bool hasStatus(const ReferenceStatus* inst) noexcept;
	const ArrayList<ReferenceStatus>* getOwnerList() const noexcept;

	//GcManager* getGC() const noexcept;
private:
	ArrayList<ReferenceStatus> ownerList;
	GcManager* gc;
};

} /* namespace alinous */

#endif /* INSTANCE_GC_GCCYCLICCHECKERCONTEXT_H_ */
