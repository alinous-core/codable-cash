/*
 * VMemHashMapKeySet.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_
#define INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_
#include "vm/VirtualMachine.h"
#include <cstddef>

namespace alinous {

template <typename T, typename V>
class VMemHashMapRawArray;
template <typename T, typename V>
class VMemHashMapInternalElement;

template <typename K, typename V>
class VMemHashMapKeySet {
public:
	VMemHashMapKeySet(const VMemHashMapKeySet& inst) = delete;
	VMemHashMapKeySet(VirtualMachine* vm) : vm(vm) {
		this->list = new(vm) VMemHashMapRawArray<K, V>(vm);
		this->nullElement = nullptr;
	}
	virtual ~VMemHashMapKeySet(){
		typename VMemHashMapRawArray<K, V>::Iterator it = this->list->iterator();
		while(it.hasNext()){
			VMemHashMapInternalElement<K, V>* element = it.next();

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

	void* operator new(size_t size, VirtualMachine* vm){
		VmMemoryManager* mem = vm->getMemory();
		uint64_t mallocSize = size + sizeof(VirtualMachine*);

		void* p = mem->malloc(mallocSize);
		VirtualMachine** vmp = (VirtualMachine**)p;
		*vmp = vm;

		return ((char*)p) + sizeof(VirtualMachine*);
	}
	void operator delete(void* p, size_t size){
		void* ptr = ((char*)p) - sizeof(VirtualMachine*);

		VirtualMachine** vm = (VirtualMachine**)ptr;
		VmMemoryManager* mem = (*vm)->getMemory();

		mem->free((char*)ptr);
	}

	V* addElement(const K *key, V* value) noexcept {
		if(key == nullptr){
			if(this->nullElement != nullptr){
				V* last = this->nullElement->value;

				this->nullElement->value = value;
				return last;
			}

			this->nullElement = new(this->vm) VMemHashMapInternalElement<K,V>(nullptr, value);

			return nullptr;
		}

		VMemHashMapInternalElement<K,V> tmp(key, value);
		VMemHashMapInternalElement<K,V>* obj = this->list->search(&tmp);

		if(obj != nullptr){
			V* last = obj->value;
			obj->value = value;

			return last;
		}

		K *newKey = new K(*key); // FIXME hash copy
		obj = new(this->vm) VMemHashMapInternalElement<K,V>(newKey, value);

		this->list->addElement(obj);

		return nullptr;
	}

	V* getValue(const K* key) const noexcept {
		if(key == nullptr){
			V* val = this->nullElement == nullptr ? nullptr : this->nullElement->value;
			return val;
		}

		VMemHashMapInternalElement<K,V> tmp(key, nullptr);
		VMemHashMapInternalElement<K,V>* obj = this->list->search(&tmp);
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
			VMemHashMapInternalElement<K,V>* obj = it.next();
			delete obj->key;
			delete obj;
		}

		this->list->reset();
	}

	void remove(K* o) noexcept {
		if(o == nullptr){
			if(this->nullElement != nullptr){
				delete this->nullElement;
				this->nullElement = nullptr;
			}

			return;
		}

		VMemHashMapInternalElement<K,V> tmp(o, nullptr);
		VMemHashMapInternalElement<K,V>* removObj = this->list->search(&tmp);
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

private:
	VMemHashMapRawArray<K, V>* list;
	VMemHashMapInternalElement<K, V>* nullElement;
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_ */
