/*
 * VMemHashMapKeySet.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_
#define INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_
#include <cstddef>

#include "vm/VirtualMachine.h"

#include "base/Iterator.h"

namespace alinous {

template <typename T, typename V>
class VMemHashMapRawArray;
template <typename T, typename V>
class VMemHashMapInternalElement;

template <typename K, typename V>
class VMemHashMapKeySet {
public:
	VMemHashMapKeySet(const VMemHashMapKeySet& inst) = delete;
	explicit VMemHashMapKeySet(VirtualMachine* vm) : vm(vm) {
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

		K *newKey = key->copy(vm);
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

	class HashMapKeySetIterator : public Iterator<K> {
	public:
		HashMapKeySetIterator(VMemHashMapRawArray<K, V>* list, VMemHashMapInternalElement<K, V>* nullelement) : Iterator<K>(),
			internalIt(list->iterator()), outputNull(false), nullElement(nullelement)
		{
		}
		virtual ~HashMapKeySetIterator() noexcept {
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

		virtual bool hasNext() {
			if(this->outputNull == false && this->nullElement != nullptr){
				return true;
			}
			return this->internalIt.hasNext();
		}
		virtual const K* next() {
			if(this->outputNull == false){
				this->outputNull = true;

				if(this->nullElement != nullptr){
					return this->nullElement->key;
				}
			}

			VMemHashMapInternalElement<K, V>* obj = this->internalIt.next();
			if(obj == nullptr){
				return nullptr;
			}
			return obj->key;
		}
		virtual void remove(){

		}
	private:
		typename VMemHashMapRawArray<K, V>::Iterator internalIt;
		bool outputNull;
		VMemHashMapInternalElement<K, V>* nullElement;
	};

	Iterator<K>* iterator() noexcept {
		HashMapKeySetIterator* iterator = new(vm) HashMapKeySetIterator(this->list, this->nullElement);

		return iterator;
	}
private:
	VMemHashMapRawArray<K, V>* list;
	VMemHashMapInternalElement<K, V>* nullElement;
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_ */
