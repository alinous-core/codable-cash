/*
 * test_linkedlist.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/RawLinkedList.h"
#include "base/Integer.h"

using namespace alinous;

TEST_GROUP(RawLinkedListTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(RawLinkedListTestGroup, construct){
	RawLinkedList<Integer> list;

	CHECK(list.size() == 0);
}

TEST(RawLinkedListTestGroup, testAdd01){
	RawLinkedList<Integer> ar;

	ar.add(new Integer(10));
	CHECK(ar.size() == 1);

	int size = ar.size();
	for(int i = 0; i != size; ++i){
		Integer* ptr = ar.get(i);
		delete ptr;
	}
}

TEST(RawLinkedListTestGroup, testAdd02){
	int maxLoop = 10;

	RawLinkedList<Integer> list;

	for(int i = 0; i != maxLoop; ++i){
		Integer* ptr = new Integer(i);
		list.add(ptr);
	}

	Integer* ptrnull = list.get(maxLoop + 1);
	CHECK(ptrnull == nullptr)

	for(int i = 0; i != maxLoop; ++i){
		Integer* ptr = list.get(i);
		delete ptr;
	}
}

TEST(RawLinkedListTestGroup, testAdd03){
	int maxLoop = 100;

	RawLinkedList<Integer> list;

	CHECK(list.isEmpty())

	for(int i = 0; i != maxLoop; ++i){
		Integer* ptr = new Integer(i);
		list.add(ptr);
	}

	CHECK(!list.isEmpty())

	for(int i = 0; i != maxLoop; ++i){
		int index = ((list.size() - 1) % 10);

		Integer* ptr = list.remove(index);
		delete ptr;
	}
}

TEST(RawLinkedListTestGroup, testAdd04){
	int maxLoop = 100;

	RawLinkedList<Integer> list;

	CHECK(list.isEmpty())

	for(int i = 0; i != maxLoop; ++i){
		int index = list.size() % (maxLoop /3);

		Integer* ptr = new Integer(i);
		list.add(index, ptr);
	}

	CHECK(!list.isEmpty())

	list.remove(maxLoop + 1);

	for(int i = 0; i != list.size(); ++i){
		Integer* ptr = list.get(i);
		delete ptr;
	}
}

TEST(RawLinkedListTestGroup, testAdd05){
	int maxLoop = 100;

	RawLinkedList<Integer> list;

	for(int i = 0; i != maxLoop; ++i){
		Integer* ptr = new Integer(i);
		list.add(ptr);
	}

	Integer dummy(-1);
	CHECK(!list.contains(&dummy))
	CHECK(list.indexOf(&dummy) < 0)
	CHECK(!list.remove(&dummy))

	int pos = 0;
	RawLinkedList<Integer>::Iterator it = list.iterator();
	while(it.hasNext()){
		Integer* ptr = it.next();

		bool c = list.contains(ptr);


		int index = list.indexOf(ptr);
		CHECK(index == pos++)
	}

	for(int i = 0; i != maxLoop; ++i){
		Integer* ptr = list.get(0);

		bool c = list.remove(ptr);
		CHECK(c)

		delete ptr;
	}
}

TEST(RawLinkedListTestGroup, testMoveElementToTop01){
	RawLinkedList<Integer> list;

	int maxLoop = 3;
	for(int i = 0; i != maxLoop; ++i){
		Integer* ptr = new Integer(i);
		list.add(ptr);
	}

	RawLinkedList<Integer>::Element* el = list.getLastElement()->prev;

	list.moveElementToTop(el);


	Integer* ptr = list.get(0);
	CHECK(ptr->value == 1)
	ptr = list.get(1);
	CHECK(ptr->value == 0)
	ptr = list.get(2);
	CHECK(ptr->value == 2)

	for(int i = 0; i != maxLoop; ++i){
		Integer* ptr = list.get(0);

		bool c = list.remove(ptr);
		CHECK(c)

		delete ptr;
	}

}



