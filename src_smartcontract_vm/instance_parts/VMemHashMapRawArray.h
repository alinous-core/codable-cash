/*
 * VMemHashMapRawArray.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAPRAWARRAY_H_
#define INSTANCE_PARTS_VMEMHASHMAPRAWARRAY_H_

#include "VMemList.h"
#include "VMemRawBitSet.h"

#include "vm/VirtualMachine.h"

#include "instance_parts/VmMalloc.h"

#include "memory/VmMemoryManager.h"

namespace alinous {

template <typename K,typename V>
class VMemHashMapInternalElement {
public:
	VMemHashMapInternalElement(const VMemHashMapInternalElement& inst) = default;
	VMemHashMapInternalElement(const K* k, V* v)  : key(k), value(v){}
	~VMemHashMapInternalElement(){
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
public:
	static const int MAX_HASH = 64;
	VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>** arrays;
	VMemRawBitSet bitset;
	int numElements;
	VirtualMachine* vm;

	VMemHashMapRawArray(const VMemHashMapRawArray& base) = delete;
	explicit VMemHashMapRawArray(VirtualMachine* vm)  :
		bitset(vm, MAX_HASH / 8), numElements(0), vm(vm)
	{
		VmMalloc* alloc = vm->getAlloc();
		// this->arrays = new ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>*[MAX_HASH];

		this->arrays = (VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>**)
				alloc->mallocPtrArray(MAX_HASH * sizeof(VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>*));

		for(int i = 0; i != MAX_HASH; ++ i){
			VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare> *ar
				= new(vm) VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>(vm, 4);
			this->arrays[i] = ar;
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

	virtual ~VMemHashMapRawArray() noexcept {
		for(int i = 0; i != MAX_HASH; ++ i){
			VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare> *ar = arrays[i];
			delete ar;
		}

		VmMalloc* alloc = vm->getAlloc();
		alloc->releaseArray(this->arrays);
		//delete [] arrays;
	}

	int size() const noexcept {
		return this->numElements;
	}
	bool isEmpty() const noexcept {
		return this->numElements == 0;
	}
	VMemHashMapInternalElement<K, V>* addElement(VMemHashMapInternalElement<K, V>* ptr) noexcept {
		int hashcode = getHash(ptr);

		arrays[hashcode]->addElementWithSorted(ptr);
		bitset.set(hashcode);
		++numElements;

		return ptr;
	}

	bool removeByObj(const VMemHashMapInternalElement<K, V>* obj) noexcept {
		int hashcode = getHash(obj);
		bool result =  arrays[hashcode]->removeByObj(obj);
		if(result){
			--numElements;
		}

		if(arrays[hashcode]->size() == 0){
			bitset.clear(hashcode);
		}

		return result;
	}

	VMemHashMapInternalElement<K, V>* search(const VMemHashMapInternalElement<K, V>* value) const noexcept {
		int hashcode = getHash(value);
		return arrays[hashcode]->search(value);
	}

	void reset() noexcept {
		for(int i = 0; i != MAX_HASH; i++){
			arrays[i]->reset();
		}
		bitset.clear();
		numElements = 0;
	}

	class Iterator {
	public:
		int hashCode;
		int index;
		VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>** arrays;
		const VMemRawBitSet* bitset;
		Iterator(VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>** ptr, VMemRawBitSet* bitset)
			: hashCode(0), index(0), arrays(ptr), bitset(bitset) {}

		bool hasNext() const {
			VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>* current = arrays[hashCode];
			if(current->size() == index){
				const int nextHash = hashCode + 1;
				if(nextHash == MAX_HASH){
					return false;
				}

				int next = bitset->nextSetBit(nextHash);
				if(next < 0){
					return false;
				}
				return true;
			}

			return true;
		}
		VMemHashMapInternalElement<K, V>* next() throw() {
			const VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>* current = arrays[hashCode];
			if(current->size() == index){
				const int nextHash = hashCode + 1;
				int next = bitset->nextSetBit(nextHash);

				if(nextHash == MAX_HASH || next < 0){
					return nullptr;
				}

				index = 0;
				hashCode = next;
			}

			current = arrays[hashCode];
			return current->get(index++);
		}
	};

	Iterator iterator() {
		return Iterator(arrays, &bitset);
	}

private:
	int getHash(const VMemHashMapInternalElement<K, V>* ptr) const noexcept {
		int num = ptr->hashCode();
		num = (num >= 0) ? num : num * -1;

		int code = (num >> 1) % MAX_HASH;
		//wprintf(L"%llx --> %d\n", num, code);

		return code;
	}
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAPRAWARRAY_H_ */
