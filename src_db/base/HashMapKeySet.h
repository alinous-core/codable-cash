/*
 * HashMapKeySet.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_HASHMAPKEYSET_H_
#define BASE_HASHMAPKEYSET_H_

namespace alinous {

template <typename T, typename V>
class HashMapRawArray;
template <typename T, typename V>
class HashMapInternalElement;

template <typename K, typename V>
class HashMapKeySet {
public:
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
	}

	V* addElement(K *key, V* value) noexcept {
		if(key == nullptr){
			if(this->nullElement != nullptr){
				V* last = this->nullElement->value;

				this->nullElement->value = value;
				return last;
			}

			K *newKey = new K(*key);
			this->nullElement = new HashMapInternalElement<K,V>(newKey, value);

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

	V* getValue(K* key) throw() {
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

	void clear() throw() {
		if(this->nullElement != nullptr){
			delete this->nullElement;
			this->nullElement = nullptr;
		}

		auto it = this->list->iterator();
		while(it.hasNext()){
			HashMapInternalElement<K,V>* obj = it.next();
			delete obj;
		}

		this->list->reset();
	}

private:
	HashMapRawArray<K, V>* list;
	HashMapInternalElement<K, V>* nullElement;
};


}

#endif /* BASE_HASHMAPKEYSET_H_ */
