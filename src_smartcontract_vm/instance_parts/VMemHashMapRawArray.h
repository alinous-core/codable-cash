/*
 * VMemHashMapRawArray.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAPRAWARRAY_H_
#define INSTANCE_PARTS_VMEMHASHMAPRAWARRAY_H_

namespace alinous {

template <typename K,typename V>
class VMemHashMapInternalElement {
public:
	VMemHashMapInternalElement(const VMemHashMapInternalElement& inst) = default;
	VMemHashMapInternalElement(const K* k, V* v)  : key(k), value(v){}
	~VMemHashMapInternalElement(){
	}

	int hashCode() const  {
		const K* keyPtr = this->key;

		return keyPtr->hashCode();
	}
	class ValueCompare {
	public:
		int operator() (const VMemHashMapInternalElement<K, V>* const a, const VMemHashMapInternalElement<K, V>* const b) const  {
			typename K::ValueCompare cmp;

			return cmp(a->key, b->key);
		}
	};

	const K* key;
	V* value;
};


template <typename K,typename V>
class VMemHashMapRawArray {
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAPRAWARRAY_H_ */
