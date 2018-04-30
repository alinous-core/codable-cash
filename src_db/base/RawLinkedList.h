/*
 * RawLinkedList.h
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#ifndef BASE_RAWLINKEDLIST_H_
#define BASE_RAWLINKEDLIST_H_

#include "RawCompare.h"

namespace alinous {

template <typename T, typename C = RawCompare>
class RawLinkedList {
public:
	class Element {
	public:
		inline Element(T* ptr) noexcept : data(ptr), next(nullptr), prev(nullptr){}

		T* data;
		Element* next;
		Element* prev;
	};
	class Iterator {
	public:
		inline Iterator(RawLinkedList<T, C>* list) noexcept : list(list), current(list->root) {}

		inline bool hasNext() noexcept {
			return current != nullptr;
		}
		inline T* next() noexcept {
			Element* prevCurent = current;
			current = current->next;
			return prevCurent->data;
		}

		inline Element* nextElement() noexcept {
			Element* prevCurent = current;
			current = current->next;
			return prevCurent;
		}
	private:
		RawLinkedList<T, C>* list;
		Element* current;
	};
protected:
	Element* root;
	Element* last;
	int length;
	const C compareFunctor;
public:
	RawLinkedList() noexcept : root(nullptr), last(nullptr), length(0), compareFunctor() {}
	~RawLinkedList() noexcept {
		clear();
	}
	inline Iterator iterator() noexcept {
		RawLinkedList<T,C>::Iterator iter(this);
		return iter;
	}
	inline void add(T* data) noexcept {
		addLast(data);
	}
	void add(int index, T* element) noexcept {
		if(index == this->length){
			addLast(element);
		}else{
			Element* e = getElement(index);
			Element* newElement = new Element(element);
			addBefore(e, newElement);
		}
	}
	void clear() noexcept {
		const int max = this->length;
		for(int i = 0; i != max; ++i){
			removeElement(this->root);
		}
		this->length = 0;
	}
	T* get(int index) noexcept {
		int i = 0;
		RawLinkedList<T,C>::Iterator it(this); // = iterator();
		while(it.hasNext()){
			T* d = it.next();

			if(i == index){
				return d;
			}
			++i;
		}
		return nullptr;
	}
	bool isEmpty() noexcept {
		return this->length == 0;
	}
	bool contains(T* o) noexcept {
		RawLinkedList<T,C>::Iterator it(this); // = iterator();
		while(it.hasNext()){
			T* d = it.next();
			if(compareFunctor(o, d) == 0){
				return true;
			}
		}
		return false;
	}
	int indexOf(T* obj) noexcept {
		int index = 0;
		RawLinkedList<T,C>::Iterator it(this); // = iterator();
		while(it.hasNext()){
			T* d = it.next();

			if(compareFunctor(obj, d) == 0){
				return index;
			}
			++index;
		}
		return -1;
	}
	T* remove(int index) noexcept {
		Element* del = getElement(index);
		if(del == nullptr){
			return nullptr;
		}

		T* ret = del->data;
		removeElement(del);

		return ret;

	}
	bool remove(T* data) noexcept {
		int index = indexOf(data);
		if(index < 0){
			return false;
		}

		Element* del = getElement(index);
		removeElement(del);


		return true;
	}

	inline int size() noexcept {
		return this->length;
	}

	void moveElementToTop(Element* element) noexcept {
		if(element == root){
			return;
		}

		if(this->last == element){
			this->last = element->prev;
		}

		element->prev->next = element->next;

		if(element->next != nullptr){
			element->next->prev = element->prev;
		}

		root->prev = element;
		element->next = root;
		element->prev = nullptr;

		root = element;

	}

protected:
	Element* getElement(int index) noexcept {
		int i = 0;
		RawLinkedList<T,C>::Iterator it(this); // = iterator();
		while(it.hasNext()){
			Element* e = it.nextElement();

			if(i == index){
				return e;
			}
			++i;
		}
		return nullptr;
	}
	void removeElement(Element* element) noexcept {
		if(element == this->root){
			#ifdef __FILEIO_DEGUB
			assert(this->length == 1 || element->next != nullptr);
			#endif


			if(element->next != nullptr){
				element->next->prev = nullptr;
			}
			this->root = element->next;

			if(element == this->last){
				this->last = element->prev;
			}

			delete element;

			this->length--;

			return;
		}else if(element == this->last){
			element->prev->next = nullptr;
			this->last = element->prev;

			delete element;

			this->length--;

			return;
		}

		element->next->prev = element->prev;
		element->prev->next = element->next;

		delete element;

		this->length--;
	}

	void addBefore(Element* lastElement, Element* element) noexcept {
		if(lastElement->prev == nullptr){ // is root
			lastElement->prev = element;

			this->root = element;
			this->root->next = lastElement;

			this->length++;

			return;
		}

		Element* parentOfLast = lastElement->prev;

		parentOfLast->next = element;
		lastElement->prev = element;

		element->prev = parentOfLast;
		element->next = lastElement;

		this->length++;
	}
	Element* addLast(T* data) noexcept {
		Element* element = new Element(data);
		if(this->root == nullptr){
			this->root = element;
			this->last = element;

			element->prev = nullptr;
			element->next = nullptr;

			this->length++;

			return element;
		}

		this->last->next = element;

		element->prev = this->last;
		element->next = nullptr;
		this->last = element;

		this->length++;

		return element;
	}


/*
	void moveElementToLast(Element* element) noexcept {
		if(element == last){
			return;
		}

		if(element->prev == nullptr){ // is root
			this->root = element->next;
			element->next->prev = nullptr;
		}
		else{
			element->prev->next = element->next;
			element->next->prev = element->prev;
		}

		this->last->next = element;
		element->prev = this->last;

		element->next = nullptr;
		this->last = element;
	}

*/
};

} /* namespace alinous */

#endif /* BASE_RAWLINKEDLIST_H_ */
