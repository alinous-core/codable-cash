/*
 * HashMapRawArray.h
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#ifndef BASE_HASHMAPRAWARRAY_H_
#define BASE_HASHMAPRAWARRAY_H_

#include "ArrayList.h"
#include "RawBitSet.h"

namespace alinous {

template <typename K,typename V>
class HashMapInternalElement {
public:
	HashMapInternalElement(const HashMapInternalElement& inst) = default;
	HashMapInternalElement(const K* k, V* v)  : key(k), value(v){}
	~HashMapInternalElement(){
	}

	const K* key;
	V* value;
	int hashCode() const  {
		const K* keyPtr = this->key;

		return keyPtr->hashCode();
	}

	class ValueCompare {
	public:
		int operator() (const HashMapInternalElement<K, V>* const a, const HashMapInternalElement<K, V>* const b) const  {
			typename K::ValueCompare cmp;

			return cmp(a->key, b->key);
		}
	};
};

template <typename K, typename V>
class HashMapRawArray {
public:
	static const int MAX_HASH = 64;
	ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>** arrays;
	RawBitSet bitset;
	int numElements;

	HashMapRawArray(const HashMapRawArray& base) = delete;
	HashMapRawArray()  :
		bitset(MAX_HASH / 8), numElements(0)
	{
		this->arrays = new ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>*[MAX_HASH];
		for(int i = 0; i != MAX_HASH; ++ i){
			ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare> *ar
				= new ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>(4);
			this->arrays[i] = ar;
		}
	}
	virtual ~HashMapRawArray() noexcept {
		for(int i = 0; i != MAX_HASH; ++ i){
			ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare> *ar = arrays[i];
			delete ar;
		}
		delete [] arrays;
	}

	int size() const noexcept {
		return this->numElements;
	}
	bool isEmpty() const noexcept {
		return this->numElements == 0;
	}
	HashMapInternalElement<K, V>* addElement(HashMapInternalElement<K, V>* ptr) noexcept {
		int hashcode = getHash(ptr);

		arrays[hashcode]->addElementWithSorted(ptr);
		bitset.set(hashcode);
		++numElements;

		return ptr;
	}

	bool removeByObj(const HashMapInternalElement<K, V>* obj) noexcept {
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
	HashMapInternalElement<K, V>* search(const HashMapInternalElement<K, V>* value) const noexcept {
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
		ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>** arrays;
		const RawBitSet* bitset;
		Iterator(ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>** ptr, RawBitSet* bitset) throw()
			: hashCode(0), index(0), arrays(ptr), bitset(bitset) {}
		bool hasNext() const throw() {
			ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>* current = arrays[hashCode];
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
		HashMapInternalElement<K, V>* next() throw() {
			const ArrayList<HashMapInternalElement<K, V>, typename HashMapInternalElement<K, V>::ValueCompare>* current = arrays[hashCode];
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

	Iterator iterator() throw() {
		return Iterator(arrays, &bitset);
	}
private:
	int getHash(const HashMapInternalElement<K, V>* ptr) const throw() {
		int num = ptr->hashCode();
		num = (num >= 0) ? num : num * -1;

		int code = (num >> 1) % MAX_HASH;
		//wprintf(L"%llx --> %d\n", num, code);

		return code;
	}
};


}



#endif /* BASE_HASHMAPRAWARRAY_H_ */
