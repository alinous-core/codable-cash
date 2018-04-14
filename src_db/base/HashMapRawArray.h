/*
 * HashMapRawArray.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_HASHMAPRAWARRAY_H_
#define BASE_HASHMAPRAWARRAY_H_

namespace alinous {

template <typename K,typename V>
class HashMapInternalElement {
public:
	HashMapInternalElement(K* k, V* v) noexcept : key(k), value(v){}
	K* key;
	V* value;
	int hashCode() const noexcept {
		K* keyPtr = this->key;

		return keyPtr->hashCode();
	}

	class ValueCompare {
	public:
		int operator() (const HashMapInternalElement<K, V>* const a, const HashMapInternalElement<K, V>* const b) const noexcept {
			typename K::ValueCompare cmp;

			return cmp(a->key, b->key);
		}
	};
};

}



#endif /* BASE_HASHMAPRAWARRAY_H_ */
