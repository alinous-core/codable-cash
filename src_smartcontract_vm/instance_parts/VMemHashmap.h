/*
 * VMemHashmap.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAP_H_
#define INSTANCE_PARTS_VMEMHASHMAP_H_

#include "VMemHashMapRawArray.h"
#include "VMemHashMapKeySet.h"

namespace alinous {

template <typename K, typename V>
class VMemHashmap {
public:
	VMemHashmap(const VMemHashmap& base) = delete;
	VMemHashmap(VirtualMachine* vm){
		this->hashMapKeySet = new VMemHashMapKeySet<K, V>();
	}
	virtual ~VMemHashmap(){
		delete this->hashMapKeySet;
	}

protected:
	VMemHashMapKeySet<K, V>* hashMapKeySet;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAP_H_ */
