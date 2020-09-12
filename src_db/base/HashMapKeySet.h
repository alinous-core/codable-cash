/*
 * HashMapKeySet.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_HASHMAPKEYSET_H_
#define BASE_HASHMAPKEYSET_H_

#include "Iterator.h"

namespace alinous {

template <typename T, typename V>
class HashMapRawArray;
template <typename T, typename V>
class HashMapInternalElement;


template <typename K, typename V>
class HashMapKeySet {
public:
	HashMapKeySet(const HashMapKeySet& inst) = delete;

	HashMapKeySet() noexcept {
		this->list = new HashMapRawArray<K, V>();
		this->nullElement = nullptr;
	}

	virtual ~HashMapKeySet() noexcept {
		typename HashMapRawArray<K, V>::Iterator it = this->list->iterator();
		while(it.hasNext()){
			HashMapInternalElement<K, V>* element = it.next();

			if(element->key != nullptr){
				delete element->key;
			}
			delete element;
		}

		delete this->list;
		if(this->nullElement != nullptr){
			delete this->nullElement;
		}
	}

	V* addElement(const K *key, V* value) noexcept {
		if(key == nullptr){
			if(this->nullElement != nullptr){
				V* last = this->nullElement->value;

				this->nullElement->value = value;
				return last;
			}

			this->nullElement = new HashMapInternalElement<K,V>(nullptr, value);

			return nullptr;
		}

		HashMapInternalElement<K,V> tmp(key, value);
		HashMapInternalElement<K,V>* obj = this->list->search(&tmp);

		if(obj != nullptr){
			V* last = obj->value;
			obj->value = value;

			return last;
		}

		K *newKey = new K(*key);
		obj = new HashMapInternalElement<K,V>(newKey, value);

		this->list->addElement(obj);

		return nullptr;
	}

	V* getValue(const K* key) const noexcept {
		if(key == nullptr){
			V* val = this->nullElement == nullptr ? nullptr : this->nullElement->value;
			return val;
		}

		HashMapInternalElement<K,V> tmp(key, nullptr);
		HashMapInternalElement<K,V>* obj = this->list->search(&tmp);
		if(obj == nullptr){
			return nullptr;
		}

		return obj->value;
	}

	void clear() noexcept {
		if(this->nullElement != nullptr){
			delete this->nullElement;
			this->nullElement = nullptr;
		}

		auto it = this->list->iterator();
		while(it.hasNext()){
			HashMapInternalElement<K,V>* obj = it.next();
			delete obj->key;
			delete obj;
		}

		this->list->reset();
	}

	void remove(const K* o) noexcept {
		if(o == nullptr){
			if(this->nullElement != nullptr){
				delete this->nullElement;
				this->nullElement = nullptr;
			}

			return;
		}


		HashMapInternalElement<K,V> tmp(o, nullptr);
		HashMapInternalElement<K,V>* removObj = this->list->search(&tmp);
		if(removObj == nullptr){
			return;
		}

		this->list->removeByObj(removObj);

		delete removObj->key;
		delete removObj;

		return;
	}

	int size() const noexcept {
		return this->nullElement == nullptr ? this->list->size() : this->list->size() + 1;
	}

	class HashMapKeySetIterator : public Iterator<K> {
	public:
		HashMapKeySetIterator(HashMapRawArray<K, V>* list, HashMapInternalElement<K, V>* nullelement)throw() : Iterator<K>(),
			internalIt(list->iterator()), outputNull(false), nullElement(nullelement)
		{
		}
		virtual ~HashMapKeySetIterator() throw() {
		}

		virtual bool hasNext() throw() {
			if(this->outputNull == false && this->nullElement != nullptr){
				return true;
			}
			return this->internalIt.hasNext();
		}
		virtual const K* next() throw() {
			if(this->outputNull == false){
				this->outputNull = true;

				if(this->nullElement != nullptr){
					return this->nullElement->key;
				}
			}

			HashMapInternalElement<K, V>* obj = this->internalIt.next();
			if(obj == nullptr){
				return nullptr;
			}
			return obj->key;
		}
		virtual void remove() throw() {
		}

	private:
		typename HashMapRawArray<K, V>::Iterator internalIt;
		bool outputNull;
		HashMapInternalElement<K, V>* nullElement;
	};

	Iterator<K>* iterator() noexcept {
		HashMapKeySetIterator* iterator = new HashMapKeySetIterator(this->list, this->nullElement);

		return iterator;
	}

private:
	HashMapRawArray<K, V>* list;
	HashMapInternalElement<K, V>* nullElement;
};


}

#endif /* BASE_HASHMAPKEYSET_H_ */
