/*
 * VMemHashMapKeySet.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_
#define INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_

namespace alinous {

template <typename T, typename V>
class VMemHashMapRawArray;
template <typename T, typename V>
class VMemHashMapInternalElement;

template <typename K, typename V>
class VMemHashMapKeySet {
public:
	VMemHashMapKeySet(const VMemHashMapKeySet& inst) = default;
	VMemHashMapKeySet(){}
	virtual ~VMemHashMapKeySet(){}


private:
	VMemHashMapRawArray<K, V>* list;
	VMemHashMapInternalElement<K, V>* nullElement;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_ */
