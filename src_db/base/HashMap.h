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

#include "debug/debugMacros.h"

namespace alinous {


template <typename K, typename V>
class HashMap {
public:
	HashMap(const HashMap& base) = delete;

	HashMap() noexcept {
		this->hashMapKeySet = new HashMapKeySet<K, V>();
	}
	virtual ~HashMap() noexcept {
		delete this->hashMapKeySet;
	}

	void clear() noexcept {
		this->hashMapKeySet->clear();
	}

	V* put(const K* key, V* value) noexcept {
		return this->hashMapKeySet->addElement(key, value);
	}
	V* put(const K& key, V* value) noexcept {
		return this->hashMapKeySet->addElement(&key, value);
	}

	V* get(const K* key) const noexcept {
		return this->hashMapKeySet->getValue(key);
	}
	V* get(const K& key) const noexcept {
		return this->hashMapKeySet->getValue(&key);
	}
	void remove(const K* key) {
		this->hashMapKeySet->remove(key);
	}

	HashMapKeySet<K, V>* keySet() const noexcept {
		return this->hashMapKeySet;
	}

	int size() const noexcept {
		return this->hashMapKeySet->size();
	}

	bool isEmpty() const noexcept {
		return size() == 0;
	}
protected:
	HashMapKeySet<K, V>* hashMapKeySet;
};


}


#endif /* BASE_HASHMAP_H_ */
