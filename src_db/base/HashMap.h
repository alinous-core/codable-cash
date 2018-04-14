/*
 * HashMap.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_HASHMAP_H_
#define BASE_HASHMAP_H_

#include "HashMapRawArray.h"
#include "HashMapKeySet.h"

namespace alinous {


template <typename K, typename V>
class HashMap {
public:
	HashMap() noexcept {
		this->hashMapKeySet = new HashMapKeySet<K, V>();
	}
	virtual ~HashMap() noexcept {
		delete this->hashMapKeySet;
	}

	V* put(K* key, V* value) noexcept {
		return this->hashMapKeySet->addElement(key, value);
	}

	V* get(K* key) noexcept {
		return this->hashMapKeySet->getValue(key);
	}
protected:
	HashMapKeySet<K, V>* hashMapKeySet;
};


}


#endif /* BASE_HASHMAP_H_ */
