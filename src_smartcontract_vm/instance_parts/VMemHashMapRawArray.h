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
public:
	static const int MAX_HASH = 64;
	VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>** arrays;
	VMemRawBitSet bitset;
	int numElements;
	VirtualMachine* vm;

	VMemHashMapRawArray(const VMemHashMapRawArray& base) = delete;
	explicit VMemHashMapRawArray(VirtualMachine* vm)  :
		bitset(MAX_HASH / 8), numElements(0), vm(vm)
	{
		VmMalloc* alloc = vm->getAlloc();
		// this->arrays = new ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>*[MAX_HASH];

		this->arrays = (VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>**)
				alloc->mallocPtrArray(MAX_HASH * sizeof(VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>*));

		for(int i = 0; i != MAX_HASH; ++ i){
			VMemList<VMemHashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare> *ar
				= new VMemList<HashMapInternalElement<K, V>, typename VMemHashMapInternalElement<K, V>::ValueCompare>(4);
			this->arrays[i] = ar;
		}
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


	};

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
