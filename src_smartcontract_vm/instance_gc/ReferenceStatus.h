/*
 * ReferenceStatus.h
 *
 *  Created on: 2019/06/08
 *      Author: iizuka
 */

#ifndef INSTANCE_GC_REFERENCESTATUS_H_
#define INSTANCE_GC_REFERENCESTATUS_H_

namespace alinous {

class AbstractVmInstance;
template <typename K, typename V> class HashMap;

class ReferenceStatus {
public:
	explicit ReferenceStatus(AbstractVmInstance* instance);
	virtual ~ReferenceStatus();


private:
	AbstractVmInstance* instance;

};

} /* namespace alinous */

#endif /* INSTANCE_GC_REFERENCESTATUS_H_ */
