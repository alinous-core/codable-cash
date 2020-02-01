/*
 * ReferenceStatusCompare.h
 *
 *  Created on: 2020/01/12
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_REFERENCESTATUSCOMPARE_H_
#define INSTANCE_GC_REFERENCESTATUSCOMPARE_H_

namespace alinous {

class ReferenceStatus;

class ReferenceStatusCompare {
public:
	friend class ReferenceStatus;
	int operator() (const ReferenceStatus* const a, const ReferenceStatus* const b) const noexcept;
};

} /* namespace alinous */

#endif /* INSTANCE_GC_REFERENCESTATUSCOMPARE_H_ */
