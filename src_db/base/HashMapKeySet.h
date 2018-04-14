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

template <typename T, typename V>
class HashMapKeySet {
public:
	HashMapKeySet() noexcept {
		this->list = new HashMapRawArray<T, V>();
		this->nullElement = nullptr;
	}

	virtual ~HashMapKeySet() noexcept {
		delete this->list;
	}

	virtual void add(T* e) throw() {
		if(e == nullptr){
			this->nullElement = new HashMapInternalElement<T, V>(nullptr, nullptr);
			return;
		}

		HashMapInternalElement<T, V> tmp(e, nullptr);
		HashMapInternalElement<T,V>* obj = this->list->search(&tmp);
		if(obj != nullptr){
			obj->value = nullptr;

			return;
		}

		HashMapInternalElement<T, V>* element = new HashMapInternalElement<T, V>(e, nullptr);

		this->list->addElement(element);
	}

	void addElement(const HashMapInternalElement<T, V>* e) throw() {
		if(e->key == nullptr){
			if(this->nullElement != nullptr){
				this->nullElement->value = e->value;
				return;
			}

			this->nullElement = new HashMapInternalElement<T,V>(e->key, e->value);

			return;
		}


		HashMapInternalElement<T,V>* obj = this->list->search(e);

		if(obj != nullptr){
			obj->value = e->value;

			return;
		}
		obj = new HashMapInternalElement<T,V>(e->key, e->value);

		this->list->addElement(obj);
	}

	V* getValue(T* key) throw() {
		if(key == nullptr){
			V* val = this->nullElement == nullptr ? nullptr : this->nullElement->value;
			return val;
		}

		HashMapInternalElement<T,V> tmp(key, nullptr);
		HashMapInternalElement<T,V>* obj = this->list->search(&tmp);
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
			HashMapInternalElement<T,V>* obj = it.next();
			delete obj;
		}

		this->list->reset();
	}

private:
	HashMapRawArray<T, V>* list;
	HashMapInternalElement<T, V>* nullElement;
};


}

#endif /* BASE_HASHMAPKEYSET_H_ */
